################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tst/GameTests.c \
../tst/KingPieceTests.c \
../tst/MoveRulesTests.c \
../tst/SinglePieceTests.c \
../tst/Tests.c 

OBJS += \
./tst/GameTests.o \
./tst/KingPieceTests.o \
./tst/MoveRulesTests.o \
./tst/SinglePieceTests.o \
./tst/Tests.o 

C_DEPS += \
./tst/GameTests.d \
./tst/KingPieceTests.d \
./tst/MoveRulesTests.d \
./tst/SinglePieceTests.d \
./tst/Tests.d 


# Each subdirectory must supply rules for building sources it contributes
tst/%.o: ../tst/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/disk/Software/workspace/checkers/c/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


