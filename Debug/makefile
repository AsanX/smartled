################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SPI_Test_RGBWSK6812.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SPI_Test_RGBWSK6812.list \

OBJCOPY_BIN += \
SPI_Test_RGBWSK6812.bin \


# All Target
all: SPI_Test_RGBWSK6812.elf secondary-outputs

# Tool invocations
SPI_Test_RGBWSK6812.elf: $(OBJS) $(USER_OBJS) C:\Users\santt\Desktop\The\ 3bit\ SPI\ SK6812\STM32F042K6TX_FLASH.ld
	arm-none-eabi-gcc -o "SPI_Test_RGBWSK6812.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\santt\Desktop\The 3bit SPI SK6812\STM32F042K6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SPI_Test_RGBWSK6812.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SPI_Test_RGBWSK6812.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SPI_Test_RGBWSK6812.list"
	@echo 'Finished building: $@'
	@echo ' '

SPI_Test_RGBWSK6812.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "SPI_Test_RGBWSK6812.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
