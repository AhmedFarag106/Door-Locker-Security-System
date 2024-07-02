################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Control_ECU.c \
../DCmotor.c \
../PWM.c \
../buzzer.c \
../external_eeprom.c \
../gpio.c \
../timer1.c \
../twi.c \
../uart.c 

OBJS += \
./Control_ECU.o \
./DCmotor.o \
./PWM.o \
./buzzer.o \
./external_eeprom.o \
./gpio.o \
./timer1.o \
./twi.o \
./uart.o 

C_DEPS += \
./Control_ECU.d \
./DCmotor.d \
./PWM.d \
./buzzer.d \
./external_eeprom.d \
./gpio.d \
./timer1.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


