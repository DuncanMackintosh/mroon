################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../renderables/Mesh.cpp \
../renderables/QuadMesh.cpp \
../renderables/Renderable.cpp 

OBJS += \
./renderables/Mesh.o \
./renderables/QuadMesh.o \
./renderables/Renderable.o 

CPP_DEPS += \
./renderables/Mesh.d \
./renderables/QuadMesh.d \
./renderables/Renderable.d 


# Each subdirectory must supply rules for building sources it contributes
renderables/%.o: ../renderables/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


