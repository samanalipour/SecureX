################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/Src/Button.c \
../Utilities/Src/Crypto.c \
../Utilities/Src/Menu.c \
../Utilities/Src/RNG.c \
../Utilities/Src/Timer.c \
../Utilities/Src/printf_redirect.c 

OBJS += \
./Utilities/Src/Button.o \
./Utilities/Src/Crypto.o \
./Utilities/Src/Menu.o \
./Utilities/Src/RNG.o \
./Utilities/Src/Timer.o \
./Utilities/Src/printf_redirect.o 

C_DEPS += \
./Utilities/Src/Button.d \
./Utilities/Src/Crypto.d \
./Utilities/Src/Menu.d \
./Utilities/Src/RNG.d \
./Utilities/Src/Timer.d \
./Utilities/Src/printf_redirect.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/Src/%.o Utilities/Src/%.su Utilities/Src/%.cyclo: ../Utilities/Src/%.c Utilities/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../X-CUBE-CRYPTOLIB/Middlewares/ST/STM32_Cryptographic/include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/saman/Desktop/SecureX/Firmware/Libraries/Inc" -I"/home/saman/Desktop/SecureX/Firmware/Utilities/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-Src

clean-Utilities-2f-Src:
	-$(RM) ./Utilities/Src/Button.cyclo ./Utilities/Src/Button.d ./Utilities/Src/Button.o ./Utilities/Src/Button.su ./Utilities/Src/Crypto.cyclo ./Utilities/Src/Crypto.d ./Utilities/Src/Crypto.o ./Utilities/Src/Crypto.su ./Utilities/Src/Menu.cyclo ./Utilities/Src/Menu.d ./Utilities/Src/Menu.o ./Utilities/Src/Menu.su ./Utilities/Src/RNG.cyclo ./Utilities/Src/RNG.d ./Utilities/Src/RNG.o ./Utilities/Src/RNG.su ./Utilities/Src/Timer.cyclo ./Utilities/Src/Timer.d ./Utilities/Src/Timer.o ./Utilities/Src/Timer.su ./Utilities/Src/printf_redirect.cyclo ./Utilities/Src/printf_redirect.d ./Utilities/Src/printf_redirect.o ./Utilities/Src/printf_redirect.su

.PHONY: clean-Utilities-2f-Src

