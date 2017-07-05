################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/blink.c \
../Source/dht11.c \
../Source/main.c \
../Source/usi_i2c_slave.c 

OBJS += \
./Source/blink.o \
./Source/dht11.o \
./Source/main.o \
./Source/usi_i2c_slave.o 

C_DEPS += \
./Source/blink.d \
./Source/dht11.d \
./Source/main.d \
./Source/usi_i2c_slave.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/urban/Documents/Projekti/Kalilnik/Kalilnik1_3/Software/Out -D_AVR_ATtiny44_ -U__AVR_ATmega16__ -Wall -g2 -gstabs -O2 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=attiny44 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


