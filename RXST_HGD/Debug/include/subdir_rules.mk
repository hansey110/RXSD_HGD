################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
include/AD7606.obj: ../include/AD7606.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.4.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=softlib --vcu_support=vcu0 --include_path="F:/PMSM_work/RXSE_PMSM" --include_path="F:/PMSM_work/RXSE_PMSM/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_18.1.4.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="include/AD7606.d_raw" --obj_directory="include" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


