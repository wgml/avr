################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
LEDS_HELLO_WORLD.lss \

FLASH_IMAGE += \
LEDS_HELLO_WORLD.hex \

EEPROM_IMAGE += \
LEDS_HELLO_WORLD.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: LEDS_HELLO_WORLD.elf secondary-outputs

# Tool invocations
LEDS_HELLO_WORLD.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,LEDS_HELLO_WORLD.map -mmcu=atmega16a -o "LEDS_HELLO_WORLD.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

LEDS_HELLO_WORLD.lss: LEDS_HELLO_WORLD.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S LEDS_HELLO_WORLD.elf  >"LEDS_HELLO_WORLD.lss"
	@echo 'Finished building: $@'
	@echo ' '

LEDS_HELLO_WORLD.hex: LEDS_HELLO_WORLD.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex LEDS_HELLO_WORLD.elf  "LEDS_HELLO_WORLD.hex"
	@echo 'Finished building: $@'
	@echo ' '

LEDS_HELLO_WORLD.eep: LEDS_HELLO_WORLD.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex LEDS_HELLO_WORLD.elf  "LEDS_HELLO_WORLD.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: LEDS_HELLO_WORLD.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16a LEDS_HELLO_WORLD.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) LEDS_HELLO_WORLD.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
