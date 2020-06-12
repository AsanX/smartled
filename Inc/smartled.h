// include guard
#ifndef SMARTLED_GUARD
#define SMARTLED_GUARD

#include <stdint.h>
#include <stdbool.h>

#ifdef STM32F042x6
#include "stm32f0xx_hal.h"
#endif

/*  this library only works, if spi speed is set to 2.5Mbit/s,
    however there is 20% tolerance, so spi speed 2Mbit...3Mbit is fine.
    If my calculations are wrong, just make sure that sending 3bits takes around 1,25uS

    Some SPI settings may not work, so it's up to you to make it work.
    
    MY SPI SETTINGS: 2Mbit/s | 2 Edge | 8 Bit mode
*/

/*	leds in array	*/
#define maxleds 	144

/*	color and bits	*/
#define colors		3

/*		codes		*/
#define code_1  	0b110
#define code_0      0b100



/* 	reset code		*/
#define reset 		10


/*	function prototypes	*/
void smartled_init(SPI_HandleTypeDef* hspi);
void smartled_set_all(uint8_t r, uint8_t g, uint8_t b);
void smartled_set(uint16_t led, uint8_t r, uint8_t g, uint8_t b);
void smartled_rgbw(uint16_t start_p, uint16_t led_count, uint8_t r, uint8_t g, uint8_t b);
void smartled_write(void);

#endif
