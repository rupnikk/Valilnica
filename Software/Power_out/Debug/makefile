################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Power_out.lss \

FLASH_IMAGE += \
Power_out.hex \

EEPROM_IMAGE += \
Power_out.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Power_out.elf secondary-outputs

dependents:
	-cd /home/urban/Documents/Projekti/Valilnica/Software/Power_out/Release && $(MAKE) all

# Tool invocations
Power_out.elf: $(OBJS) $(USER_OBJS) /home/urban/Documents/Projekti/Valilnica/Software/Power_out/Release/Power_out.elf
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Power_out.map -mmcu=attiny85 -o "Power_out.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Power_out.lss: Power_out.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Power_out.elf  >"Power_out.lss"
	@echo 'Finished building: $@'
	@echo ' '

Power_out.hex: Power_out.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Power_out.elf  "Power_out.hex"
	@echo 'Finished building: $@'
	@echo ' '

Power_out.eep: Power_out.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Power_out.elf  "Power_out.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Power_out.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny85 Power_out.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Power_out.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:
/home/urban/Documents/Projekti/Valilnica/Software/Power_out/Release/Power_out.elf:

-include ../makefile.targets
