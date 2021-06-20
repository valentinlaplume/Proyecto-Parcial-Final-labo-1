################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Articulo.c \
../src/Controller.c \
../src/Dictionary.c \
../src/Informe.c \
../src/LinkedList.c \
../src/Parser.c \
../src/PosicionArancelaria.c \
../src/Serializer.c \
../src/TransporteAereo.c \
../src/TransporteMaritimo.c \
../src/laplume.c \
../src/main_Parcial2.c \
../src/utn.c 

OBJS += \
./src/Articulo.o \
./src/Controller.o \
./src/Dictionary.o \
./src/Informe.o \
./src/LinkedList.o \
./src/Parser.o \
./src/PosicionArancelaria.o \
./src/Serializer.o \
./src/TransporteAereo.o \
./src/TransporteMaritimo.o \
./src/laplume.o \
./src/main_Parcial2.o \
./src/utn.o 

C_DEPS += \
./src/Articulo.d \
./src/Controller.d \
./src/Dictionary.d \
./src/Informe.d \
./src/LinkedList.d \
./src/Parser.d \
./src/PosicionArancelaria.d \
./src/Serializer.d \
./src/TransporteAereo.d \
./src/TransporteMaritimo.d \
./src/laplume.d \
./src/main_Parcial2.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


