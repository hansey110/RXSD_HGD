################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./AD2S1210.obj" \
"./AD7606.obj" \
"./CLAShareData.obj" \
"./F2806x_Adc.obj" \
"./F2806x_CodeStartBranch.obj" \
"./F2806x_CpuTimers.obj" \
"./F2806x_DefaultIsr.obj" \
"./F2806x_EPwm.obj" \
"./F2806x_GlobalVariableDefs.obj" \
"./F2806x_PieCtrl.obj" \
"./F2806x_PieVect.obj" \
"./F2806x_Sci.obj" \
"./F2806x_Spi.obj" \
"./F2806x_SysCtrl.obj" \
"./F2806x_usDelay.obj" \
"./Flash28069API.obj" \
"./Servo.obj" \
"./ServoModule.obj" \
"./main.obj" \
"../28069_RAM_CLA_C_lnk.cmd" \
"../Example_Flash2806x_SW_API.cmd" \
"../F2806x_Headers_nonBIOS.cmd" \
"../lib/2805x_CLADataROMSymbols_revA.lib" \
"../lib/2806x_BootROM_API_TABLE_Symbols.lib" \
"../lib/2837x_c1bootROM_CLADataROMSymbols.lib" \
"../lib/2837x_c1bootROM_CLADataROMSymbols_fpu32.lib" \
"../lib/Flash2803x_API_V100.lib" \
"../lib/Flash2806x_API_V100.lib" \
"../lib/cla0_math_library.lib" \
"../lib/cla0_math_library_datarom.lib" \
"../lib/cla0_math_library_datarom_fpu32.lib" \
"../lib/cla0_math_library_fpu32.lib" \
"../lib/cla1_math_library.lib" \
"../lib/cla1_math_library_datarom.lib" \
"../lib/cla1_math_library_datarom_fpu32.lib" \
"../lib/cla1_math_library_fpu32.lib" \
"../lib/rts2800_ml.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include lib/subdir_vars.mk
-include subdir_rules.mk
-include lib/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RXST_HGD.out \

EXE_OUTPUTS__QUOTED += \
"RXST_HGD.out" \

BIN_OUTPUTS += \
RXST_HGD.hex \

BIN_OUTPUTS__QUOTED += \
"RXST_HGD.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "RXST_HGD.out"

# Tool invocations
RXST_HGD.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=softlib --vcu_support=vcu0 -g --diag_warning=225 --diag_wrap=off --display_error_number -z -m"RXST_HGD.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/lib" -i"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="RXST_HGD_linkInfo.xml" --rom_model -o "RXST_HGD.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

RXST_HGD.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-c2000_20.2.1.LTS/bin/hex2000"  -o "RXST_HGD.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "AD2S1210.obj" "AD7606.obj" "CLAShareData.obj" "F2806x_Adc.obj" "F2806x_CodeStartBranch.obj" "F2806x_CpuTimers.obj" "F2806x_DefaultIsr.obj" "F2806x_EPwm.obj" "F2806x_GlobalVariableDefs.obj" "F2806x_PieCtrl.obj" "F2806x_PieVect.obj" "F2806x_Sci.obj" "F2806x_Spi.obj" "F2806x_SysCtrl.obj" "F2806x_usDelay.obj" "Flash28069API.obj" "Servo.obj" "ServoModule.obj" "main.obj" 
	-$(RM) "AD2S1210.d" "AD7606.d" "CLAShareData.d" "F2806x_Adc.d" "F2806x_CpuTimers.d" "F2806x_DefaultIsr.d" "F2806x_EPwm.d" "F2806x_GlobalVariableDefs.d" "F2806x_PieCtrl.d" "F2806x_PieVect.d" "F2806x_Sci.d" "F2806x_Spi.d" "F2806x_SysCtrl.d" "Flash28069API.d" "ServoModule.d" "main.d" 
	-$(RM) "Servo.d" 
	-$(RM) "F2806x_CodeStartBranch.d" "F2806x_usDelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

