################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bootloader/bl_eth_loop.c \
../Bootloader/bl_mem_loop.c 

OBJS += \
./Bootloader/bl_eth_loop.o \
./Bootloader/bl_mem_loop.o 

C_DEPS += \
./Bootloader/bl_eth_loop.d \
./Bootloader/bl_mem_loop.d 


# Each subdirectory must supply rules for building sources it contributes
Bootloader/bl_eth_loop.o: ../Bootloader/bl_eth_loop.c Bootloader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"/home/asanchez/STM32CubeIDE/workspace_1.6.1/MyFirstBootloader/Bootloader" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bootloader/bl_eth_loop.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Bootloader/bl_mem_loop.o: ../Bootloader/bl_mem_loop.c Bootloader/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H743xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I"/home/asanchez/STM32CubeIDE/workspace_1.6.1/MyFirstBootloader/Bootloader" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Bootloader/bl_mem_loop.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

