################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
httpcli.obj: G:/My\ Drive/EEC\ 172/cc3200-sdk/netapps/http/client/httpcli.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --float_support=none -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/webclient" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/oslib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=cc3200 --define=__SL__ --define=__CCS__ --define=HTTPCli_LIBTYPE_MIN --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="httpcli.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

httpstr.obj: G:/My\ Drive/EEC\ 172/cc3200-sdk/netapps/http/client/httpstr.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --float_support=none -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/webclient" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/oslib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=cc3200 --define=__SL__ --define=__CCS__ --define=HTTPCli_LIBTYPE_MIN --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="httpstr.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

lookup.obj: G:/My\ Drive/EEC\ 172/cc3200-sdk/netapps/http/client/lookup.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --float_support=none -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/webclient" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/oslib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=cc3200 --define=__SL__ --define=__CCS__ --define=HTTPCli_LIBTYPE_MIN --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="lookup.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ssock.obj: G:/My\ Drive/EEC\ 172/cc3200-sdk/netapps/http/client/ssock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --float_support=none -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/webclient" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/oslib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=cc3200 --define=__SL__ --define=__CCS__ --define=HTTPCli_LIBTYPE_MIN --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="ssock.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


