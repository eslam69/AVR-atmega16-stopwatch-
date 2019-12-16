################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mini\ proj.c 

OBJS += \
./mini\ proj.o 

C_DEPS += \
./mini\ proj.d 


# Each subdirectory must supply rules for building sources it contributes
mini\ proj.o: ../mini\ proj.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"mini proj.d" -MT"mini\ proj.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


