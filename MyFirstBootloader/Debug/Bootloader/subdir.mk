################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bootloader/bootloader_sd.c 

OBJS += \
./Bootloader/bootloader_sd.o 

C_DEPS += \
./Bootloader/bootloader_sd.d 


# Each subdirectory must supply rules for building sources it contributes
Bootloader/bootloader_sd.o: ../Bootloader/bootloader_sd.c Bootloader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"/home/asanchez/STM32CubeIDE/workspace_1.6.1/MyFirstBootloader/Bootloader" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bootloader/bootloader_sd.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
