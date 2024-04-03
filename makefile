# master makefile to build project, several targets have been defined with the aim to ease an
# easy handling of the most common task in a project like
# - make 		- To build the project
# - maek clean	- Remove Build folder with objects and binaries
# - make flash 	- Flash the board
# - make open	- Open a SW connection with the target
# - make debug	- OpenGDB ansd start a debug session
# - make lint	- Run cppcheck with MISRA validation
# - make docs	- Run doxygen to extract documentation from code
# - make test	- Run unit tests with code coverage using ceedling

# Project name - it's mandatory to name it as is in the CPU container and the oil file.
TARGET = CasioCANplus
# Files to compile
SRCS  = main.c serial.c ints.c msps.c
SRCS += stm32g0xx_hal.c stm32g0xx_hal_cortex.c stm32g0xx_hal_rcc.c stm32g0xx_hal_flash.c
SRCS += stm32g0xx_hal_gpio.c stm32g0xx_hal_fdcan.c 
# Trampoline kernel files
SRCS +=	tpl_os_kernel.c tpl_os_timeobj_kernel.c tpl_os_action.c tpl_os_error.c	 
SRCS += tpl_os_os_kernel.c tpl_os_os.c tpl_os_interrupt_kernel.c tpl_os_task_kernel.c
SRCS += tpl_os_resource_kernel.c tpl_os_alarm_kernel.c 
SRCS += tpl_com_internal_com.c tpl_com_message_kernel.c tpl_com_queue.c
SRCS += tpl_com_app_copy.c tpl_com_errorhook.c tpl_com_filtering.c tpl_com_filters.c tpl_com_notification.c
# Trampoline board specific files
SRCS += tpl_machine_cortex.c tpl_sc_handler.S tpl_startup.S sys_handlers.c tpl_ctx_switch.S
SRCS += tpl_ctx_switch_under_it.S tpl_interrupts.S startup_stm32g0b1.c
# Trampoline app conf files
SRCS += tpl_app_config.c tpl_dispatch_table.c tpl_invoque.S tpl_primary_irq.S tpl_vectors.c 
SRCS += tpl_external_interrupts.c tpl_app_interrupts.c startup_stm32g0b1.c system_stm32g0xx.c
SRCS += tpl_machine_stm32g0b1.c pinAccess.c tpl_trace.c

# linker file
LINKER = $(TARGET)/script.ld		#this linker script name can be changed in the oil file
# Global symbols (#defines)
SYMBOLS = -DSTM32G0B1xx -DUSE_HAL_DRIVER
# directories with source files to compile (.c y .s)
SRC_PATHS  = $(TARGET)
SRC_PATHS += app
#trampoline source directories
SRC_PATHS += trampolineRTOS/machines/cortex-m
SRC_PATHS += trampolineRTOS/machines/cortex-m/armv6m
SRC_PATHS += trampolineRTOS/machines/cortex-m/armv6m/stm32g0b1
SRC_PATHS += trampolineRTOS/machines/cortex-m/armv6m/stm32g0b1/lib
SRC_PATHS += trampolineRTOS/machines/cortex-m/armv6m/stm32g0b1/STM32G0xx_HAL_Driver/Src
SRC_PATHS += trampolineRTOS/os
SRC_PATHS += trampolineRTOS/ioc
SRC_PATHS += trampolineRTOS/com

# directories with header files
INC_PATHS  = .
INC_PATHS += app
#trampoline directories
INC_PATHS += trampolineRTOS/machines/cortex-m/CMSIS/Include
INC_PATHS += trampolineRTOS/machines/cortex-m
INC_PATHS += trampolineRTOS/machines/cortex-m/armv6m
INC_PATHS += trampolineRTOS/machines/cortex-m/armv6m/stm32g0b1/
INC_PATHS += trampolineRTOS/machines/cortex-m/armv6m/stm32g0b1/lib
INC_PATHS += trampolineRTOS/machines/cortex-m/armv6m/stm32g0b1/CMSIS/Device/ST/STM32G0xx/Include
INC_PATHS += trampolineRTOS/machines/cortex-m/armv6m/stm32g0b1/STM32G0xx_HAL_Driver/Inc
INC_PATHS += trampolineRTOS/os
INC_PATHS += trampolineRTOS/ioc
INC_PATHS += trampolineRTOS/com
INC_PATHS += trampolineRTOS/debug
INC_PATHS += $(TARGET)


# -------------------------------------------------------------------------------------------------
# NOTE: From this point do not edit anything at least you know what your are doing
# ------------------------------------------------------------------------------------------------- 
TOOLCHAIN = arm-none-eabi
CPU = -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft

# compiler flags
CFLAGS  = $(CPU)
CFLAGS += -O0                        # Compile with Size Optimizations (O0, O1, O2, O3, Os)
CFLAGS += -g3                        # Debugging information level (g1, g2, g3)
CFLAGS += -ffunction-sections        # Create a separate function section
CFLAGS += -fdata-sections            # Create a separate data section
CFLAGS += -fno-builtin               # Don't recognize built-in functions that do not begin with ‘__builtin_’ as prefix
CFLAGS += -std=c11                   # Comply with C11
CFLAGS += -Wall                      # Be anal Enable All Warnings
CFLAGS += -pedantic                  # Be extra anal More ANSI Checks
CFLAGS += -Wstrict-prototypes        # Warn if a function is declared or defined without specifying the argument types
CFLAGS += -fsigned-char              # char is treated as signed
CFLAGS += -fdiagnostics-color=always # color the output
CFLAGS += -fomit-frame-pointer       # Don't keep the frame pointer in a register for functions that don't need one
CFLAGS += -fverbose-asm              # Put extra commentary information in the generated assembly code
CFLAGS += -MMD -MP

# assembler flags
AFLAGS = $(CPU)

# linker flags
LFLAGS  = $(CPU) 
LFLAGS += -Wl,--gc-sections
LFLAGS += --specs=rdimon.specs 			# link with semihosting 
LFLAGS += --specs=nano.specs 			# nano version of stdlib
LFLAGS += -Wl,-Map=build/$(TARGET).map	# Generate map file 

# Linter ccpcheck flags
LNFLAGS  = --inline-suppr       # comments to suppress lint warnings
LNFLAGS += --quiet              # spit only useful information
LNFLAGS += --enable=warning,style # enable only warnings
LNFLAGS += --error-exitcode=1	# return error if any warnings
LNFLAGS += --std=c11            # check against C11
LNFLAGS += --template=gcc       # display warning gcc style
LNFLAGS += --force              # evaluate all the #if sentences
LNFLAGS += --platform=unix32    # lint againt a unix32 platform, but we are using arm32
LNFLAGS += --cppcheck-build-dir=build/lint

# prefix substitution 
OBJS = $(SRCS:%.c=build/obj/%.o)
OBJS := $(OBJS:%.S=build/obj/%.o)
DEPS = $(OBJS:%.o=%.d)

# set source and header directories variables
VPATH = $(SRC_PATHS)
INCLS = $(addprefix -I ,$(INC_PATHS))

#---Build project----------------------------------------------------------------------------------
all : build $(TARGET)

$(TARGET) : $(addprefix build/, $(TARGET).elf)
	$(TOOLCHAIN)-objcopy -Oihex $< build/$(TARGET).hex
	$(TOOLCHAIN)-objdump -S $< > build/$(TARGET).lst
	$(TOOLCHAIN)-size --format=berkeley $<

build/$(TARGET).elf : $(OBJS)
	$(TOOLCHAIN)-gcc $(LFLAGS) -T $(LINKER) -o $@ $^

build/obj/%.o : %.c
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLS) $(SYMBOLS) -o $@ -c $<

build/obj/%.o : %.S
	$(TOOLCHAIN)-gcc $(CFLAGS) $(INCLS) $(SYMBOLS) -o $@ -c $<

-include $(DEPS)

.PHONY : build clean flash flash open debug docs lint test format goil

#---Make directory to place all the generated bynaries for build, docs, lint and test--------------
build :
	mkdir -p build/obj

#---Erase fodler with program binaries-------------------------------------------------------------
clean :
	rm -rf build $(TARGET)

#---flash the image into the mcu-------------------------------------------------------------------
flash :
	openocd -f board/st_nucleo_g0.cfg -c "program build/$(TARGET).hex verify reset" -c shutdown

#---open a debug server conection------------------------------------------------------------------
open :
	openocd -f board/st_nucleo_g0.cfg
#	JLinkGDBServer -if SWD -device stm32g0b1re -nogui

#---launch a debug session, NOTE: is mandatory to previously open a debug server session-----------
debug :
	arm-none-eabi-gdb build/$(TARGET).elf -iex "set auto-load safe-path /"

#---Genrete project documentation with doxygen-----------------------------------------------------
docs : build
	mkdir -p build/doxygen
	doxygen .doxyfile
	firefox Build/doxygen/html/index.html

#---Run Static analysis plus MISRA-----------------------------------------------------------------
lint : build
	mkdir -p build/lint
	cppcheck --addon=misra.json --suppressions-list=.msupress $(LNFLAGS) app

#---Run unit testing with code coverage using ceedling---------------------------------------------
test : build
	ceedling clobber
	ceedling gcov:all utils:gcov

#---format code using clang format-----------------------------------------------------------------
format :
	clang-format -style=file -i $(shell find app -iname *.h -o -iname *.c)
	clang-format -style=file -i $(shell find test -iname *.h -o -iname *.c)

goil :
	goil --target=cortex-m/armv6m/stm32g0b1 --templates=trampolineRTOS/goil/templates/ $(TARGET).oil