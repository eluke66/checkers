################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Board.c \
../src/Checkers-C.c \
../src/ConsolePlayer.c \
../src/Events.c \
../src/Game.c \
../src/Move.c \
../src/MoveRules.c \
../src/Piece.c \
../src/RandomChoicePlayer.c 

OBJS += \
./src/Board.o \
./src/Checkers-C.o \
./src/ConsolePlayer.o \
./src/Events.o \
./src/Game.o \
./src/Move.o \
./src/MoveRules.o \
./src/Piece.o \
./src/RandomChoicePlayer.o 

C_DEPS += \
./src/Board.d \
./src/Checkers-C.d \
./src/ConsolePlayer.d \
./src/Events.d \
./src/Game.d \
./src/Move.d \
./src/MoveRules.d \
./src/Piece.d \
./src/RandomChoicePlayer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


