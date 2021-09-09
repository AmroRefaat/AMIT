################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DIO_program.c \
../Delay_program.c \
../INT_program.c \
../S_SEGMENT.c \
../TIMER_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./DIO_program.o \
./Delay_program.o \
./INT_program.o \
./S_SEGMENT.o \
./TIMER_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./DIO_program.d \
./Delay_program.d \
./INT_program.d \
./S_SEGMENT.d \
./TIMER_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


