
#include "smartled.h"
#include <string.h>

#ifdef STM32F042x6
#include "main.h"
#endif

#ifdef HAL_SPI_MODULE_ENABLED
#include "stm32f0xx_hal.h"
#endif


/* led data length */
#define data_length  maxleds*colors*3+reset

/* led data to send */
uint8_t led_array[data_length];

/*	spi init	*/
SPI_HandleTypeDef* spi;

void smartled_init(SPI_HandleTypeDef* hspi) {

	spi = hspi;

	/* setup led array, dont touch this */
	for(uint16_t i = 0; i < data_length - reset; i=i+3) {
		led_array[i] = 219;
		led_array[i+1] = 109;
		led_array[i+2] = 182;
	}
	smartled_set_all(0,0,0);
}

void smartled_set_all(uint8_t r, uint8_t g, uint8_t b) {

	for(uint16_t i = 0; i < maxleds+1; i++) {
		smartled_set(i, r, g, b);
	}
	smartled_write();
}

void smartled_set(uint16_t led, uint8_t r, uint8_t g, uint8_t b) {

	uint16_t pos = 0;
	uint8_t col[colors] = {g,r,b};

    /* skip leds that wont change (offset) */
	if(led > 0)
		pos += colors*3*(led-1);
	else
		pos += colors*3*(led);

	for(uint8_t i = 0; i < colors; i++) {

		if(col[i] & (1<<7))
			led_array[i * 3 + pos] |= 1 << 6;			// 0b0000 0000 -> 0b1100 0000
		else
			led_array[i * 3 + pos] &= ~(1 << 6);		// 0b0000 0000 -> 0b1000 0000


		if(col[i] & (1<<6))
			led_array[i * 3 + pos] |= 1 << 3;			// 0b1100 0000 -> 0b1101 1000
		else
			led_array[i * 3 + pos] &= ~(1 << 3);		// 0b1000 0000 -> 0b1001 0000

		/*  2 bits    */
		if(col[i] & (1<<5))
			led_array[i * 3 + pos] |= 1 << 0;			// 0b1101 1000 -> 0b1101 1011
		else
			led_array[i * 3 + pos] &= ~(1 << 0);		// 0b1101 1000 -> 0b1101 1010

		/*  leave last bit to 0 (MSB)   */
		if(col[i] & (1<<4))
			led_array[i * 3 + 1 + pos] |= 1 << 5;		// 0b0000 0000 -> 0b0110 0000
		else
			led_array[i * 3 + 1 + pos] &= ~(1 << 5);	// 0b0000 0000 -> 0b0100 0000

		if(col[i] & (1<<3))
			led_array[i * 3 + 1 + pos] |= 1 << 2;		// 0b0000 0000 -> 0b0110 1100
		else
			led_array[i * 3 + 1 + pos] &= ~(1 << 2);	// 0b0000 0000 -> 0b0100 1000

		/*  set 1 bit   */
		led_array[i * 3 + 1 + pos] |= 1 << 0;	    	// 0b0000 0000 -> 0b0100 1001

		if(col[i] & (1<<2))
			led_array[i * 3 + 2 + pos] |= 1 << 7;	    // 0b0000 0000 -> 0b1000 0000
		else
			led_array[i * 3 + 2 + pos] &= ~(1 << 7);	// 0b0000 0000 -> 0b0000 0000

		if(col[i] & (1<<1))
			led_array[i * 3 + 2 + pos] |= 1 << 4;		// 0b0000 0000 -> 0b1011 0000
		else
			led_array[i * 3 + 2 + pos] &= ~(1 << 4);	// 0b0000 0000 -> 0b0010 0000

		if(col[i] & (1<<0))
			led_array[i * 3 + 2 + pos] |= 1 << 1;		// 0b0000 0000 -> 0b1011 0110
		else
			led_array[i * 3 + 2 + pos] &= ~(1 << 1);	// 0b0000 0000 -> 0b0010 0100
	    }
}

/*	write data 	*/
void smartled_write(void) {
	HAL_SPI_Transmit(spi, led_array, data_length, 100);
}

/* set one led data */
void smartled_rgbw(uint16_t start_p, uint16_t led_count, uint8_t r, uint8_t g, uint8_t b) {

    uint16_t pos = 0;
	uint8_t col[colors] = {g,r,b};

	uint16_t shift = start_p*colors*3;

    /* 	encode r g b w decimal values, start with red
		please do not touch this section of the code	*/
    for(uint16_t a = 0; a < led_count; a++) {
		if(a>0)
			pos+=colors*3;
		for(uint8_t i = 0; i < colors; i++) {

			if(col[i] & (1<<7))
				led_array[(i * 3) + pos + shift] |= 1 << 6;			// 0b0000 0000 -> 0b1100 0000
			else
				led_array[i * 3 + pos + shift] &= ~(1 << 6);		// 0b0000 0000 -> 0b1000 0000

			if(col[i] & (1<<6))
				led_array[i * 3 + pos + shift] |= 1 << 3;			// 0b1100 0000 -> 0b1101 1000
			else
				led_array[i * 3 + pos + shift] &= ~(1 << 3);		// 0b1000 0000 -> 0b1001 0000

			/*  2 bits    */
			if(col[i] & (1<<5))
				led_array[i * 3 + pos + shift] |= 1 << 0;			// 0b1101 1000 -> 0b1101 1011
			else
				led_array[i * 3 + pos + shift] &= ~(1 << 0);		// 0b1101 1000 -> 0b1101 1010

			/*  leave last bit to 0 (MSB)   */
			if(col[i] & (1<<4))
				led_array[i * 3 + 1 + pos + shift] |= 1 << 5;		// 0b0000 0000 -> 0b0110 0000
			else
				led_array[i * 3 + 1 + pos + shift] &= ~(1 << 5);	// 0b0000 0000 -> 0b0100 0000

			if(col[i] & (1<<3))
				led_array[i * 3 + 1 + pos + shift] |= 1 << 2;		// 0b0000 0000 -> 0b0110 1100
			else
				led_array[i * 3 + 1 + pos + shift] &= ~(1 << 2);	// 0b0000 0000 -> 0b0100 1000

			/*  set 1 bit   */
			led_array[i * 3 + 1 + pos + shift] |= 1 << 0;	    	// 0b0000 0000 -> 0b0100 1001

			if(col[i] & (1<<2))
				led_array[i * 3 + 2 + pos + shift] |= 1 << 7;	    // 0b0000 0000 -> 0b1000 0000
			else
				led_array[i * 3 + 2 + pos + shift] &= ~(1 << 7);	// 0b0000 0000 -> 0b0000 0000

			if(col[i] & (1<<1))
				led_array[i * 3 + 2 + pos + shift] |= 1 << 4;		// 0b0000 0000 -> 0b1011 0000
			else
				led_array[i * 3 + 2 + pos + shift] &= ~(1 << 4);	// 0b0000 0000 -> 0b0010 0000

			if(col[i] & (1<<0))
				led_array[i * 3 + 2 + pos + shift] |= 1 << 1;		// 0b0000 0000 -> 0b1011 0110
			else
				led_array[i * 3 + 2 + pos + shift] &= ~(1 << 1);	// 0b0000 0000 -> 0b0010 0100
		}
    }

	/*	send big pile of shit	*/
    /*	here u have to use ur own spi send function	*/
    smartled_write();
}
