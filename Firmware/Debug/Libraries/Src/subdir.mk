################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/Src/MY_FLASH.c \
../Libraries/Src/cmox_low_level.c \
../Libraries/Src/ssd1306.c \
../Libraries/Src/ssd1306_fonts.c 

OBJS += \
./Libraries/Src/MY_FLASH.o \
./Libraries/Src/cmox_low_level.o \
./Libraries/Src/ssd1306.o \
./Libraries/Src/ssd1306_fonts.o 

C_DEPS += \
./Libraries/Src/MY_FLASH.d \
./Libraries/Src/cmox_low_level.d \
./Libraries/Src/ssd1306.d \
./Libraries/Src/ssd1306_fonts.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Src/%.o Libraries/Src/%.su Libraries/Src/%.cyclo: ../Libraries/Src/%.c Libraries/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../X-CUBE-CRYPTOLIB/Middlewares/ST/STM32_Cryptographic/include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I"/home/saman/Desktop/SecureX/Firmware/Libraries/Inc" -I"/home/saman/Desktop/SecureX/Firmware/Utilities/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-Src

clean-Libraries-2f-Src:
	-$(RM) ./Libraries/Src/MY_FLASH.cyclo ./Libraries/Src/MY_FLASH.d ./Libraries/Src/MY_FLASH.o ./Libraries/Src/MY_FLASH.su ./Libraries/Src/cmox_low_level.cyclo ./Libraries/Src/cmox_low_level.d ./Libraries/Src/cmox_low_level.o ./Libraries/Src/cmox_low_level.su ./Libraries/Src/ssd1306.cyclo ./Libraries/Src/ssd1306.d ./Libraries/Src/ssd1306.o ./Libraries/Src/ssd1306.su ./Libraries/Src/ssd1306_fonts.cyclo ./Libraries/Src/ssd1306_fonts.d ./Libraries/Src/ssd1306_fonts.o ./Libraries/Src/ssd1306_fonts.su

.PHONY: clean-Libraries-2f-Src

