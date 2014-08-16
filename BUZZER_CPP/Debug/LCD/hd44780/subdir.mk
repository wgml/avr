################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LCD/hd44780/hd44780.c \
../LCD/hd44780/lcd.c 

OBJS += \
./LCD/hd44780/hd44780.o \
./LCD/hd44780/lcd.o 

C_DEPS += \
./LCD/hd44780/hd44780.d \
./LCD/hd44780/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
LCD/hd44780/%.o: ../LCD/hd44780/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16a -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


