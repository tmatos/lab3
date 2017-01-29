################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)
CG_TOOL_ROOT := C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./dependencias/lib/bsl/ezdsp5502_mcbsp.obj" \
"./dependencias/lib/bsl/ezdsp5502_i2cgpio.obj" \
"./dependencias/lib/bsl/ezdsp5502_i2c.obj" \
"./dependencias/lib/bsl/ezdsp5502_gpio.obj" \
"./dependencias/lib/bsl/ezdsp5502.obj" \
"./main.obj" \
"./fpa_core.obj" \
"./aic3204_tone_headphone.obj" \
"./aic3204_test.obj" \
"./aic3204_loop_linein.obj" \
-l"csl5502x.lib" \
-l"ezdsp5502bsl.lib" \
-l"rts55x.lib" \
"../lnkx.cmd" \
"../dependencias/lib/ezdsp5502bsl.lib" \
"../dependencias/C55xxCSL/lib/csl5501.lib" \
"../dependencias/C55xxCSL/lib/csl5501x.lib" \
"../dependencias/C55xxCSL/lib/csl5502.lib" \
"../dependencias/C55xxCSL/lib/csl5502x.lib" \
"../dependencias/C55xxCSL/lib/csl5509.lib" \
"../dependencias/C55xxCSL/lib/csl5509a.lib" \
"../dependencias/C55xxCSL/lib/csl5509ax.lib" \
"../dependencias/C55xxCSL/lib/csl5509x.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG1_0.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG1_0x.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG1_2.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG1_2x.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG2_0.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG2_0x.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG2_1.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG2_1x.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG2_2.lib" \
"../dependencias/C55xxCSL/lib/csl5510PG2_2x.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include dependencias/lib/subdir_vars.mk
-include dependencias/lib/bsl/subdir_vars.mk
-include dependencias/C55xxCSL/lib/subdir_vars.mk
-include subdir_rules.mk
-include dependencias/lib/subdir_rules.mk
-include dependencias/lib/bsl/subdir_rules.mk
-include dependencias/C55xxCSL/lib/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: fpafir.out


# Tool invocations
fpafir.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	@echo 'Flags: -v5502 -g --diag_warning=225 --ptrdiff_size=32 --memory_model=large -z -m"fpafir.map" --warn_sections -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" -i"C:/Documents and Settings/Tiago/Desktop/LAB3/fpa_fir/dependencias/lib" -i"C:/Documents and Settings/Tiago/Desktop/LAB3/fpa_fir/dependencias/C55xxCSL/lib" --reread_libs --rom_model'
	$(shell echo -v5502 -g --diag_warning=225 --ptrdiff_size=32 --memory_model=large -z -m"fpafir.map" --warn_sections -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/include" -i"C:/Documents and Settings/Tiago/Desktop/LAB3/fpa_fir/dependencias/lib" -i"C:/Documents and Settings/Tiago/Desktop/LAB3/fpa_fir/dependencias/C55xxCSL/lib" --reread_libs --rom_model > "ccsLinker.opt")
	$(shell type "ccsObjs.opt" >> "ccsLinker.opt")
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -@"ccsLinker.opt" -o "fpafir.out"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QTD) "fpafir.out"
	-$(RM) ".\aic3204_loop_linein.obj" ".\aic3204_test.obj" ".\aic3204_tone_headphone.obj" ".\fpa_core.obj" ".\main.obj" ".\dependencias\lib\bsl\ezdsp5502.obj" ".\dependencias\lib\bsl\ezdsp5502_gpio.obj" ".\dependencias\lib\bsl\ezdsp5502_i2c.obj" ".\dependencias\lib\bsl\ezdsp5502_i2cgpio.obj" ".\dependencias\lib\bsl\ezdsp5502_mcbsp.obj" 
	-$(RM) ".\aic3204_loop_linein.pp" ".\aic3204_test.pp" ".\aic3204_tone_headphone.pp" ".\fpa_core.pp" ".\main.pp" ".\dependencias\lib\bsl\ezdsp5502.pp" ".\dependencias\lib\bsl\ezdsp5502_gpio.pp" ".\dependencias\lib\bsl\ezdsp5502_i2c.pp" ".\dependencias\lib\bsl\ezdsp5502_i2cgpio.pp" ".\dependencias\lib\bsl\ezdsp5502_mcbsp.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
