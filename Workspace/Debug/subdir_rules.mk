################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/SpotifyController" --include_path="G:/My Drive/EEC 172/cc3200-sdk/example/common/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/json/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=ccs --define=cc3200 --define=__SL__ -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

network_common.obj: G:/My\ Drive/EEC\ 172/cc3200-sdk/example/common/network_common.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/SpotifyController" --include_path="G:/My Drive/EEC 172/cc3200-sdk/example/common/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/json/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=ccs --define=cc3200 --define=__SL__ -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="network_common.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_ccs.obj: G:/My\ Drive/EEC\ 172/cc3200-sdk/example/common/startup_ccs.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/SpotifyController" --include_path="G:/My Drive/EEC 172/cc3200-sdk/example/common/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/json/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=ccs --define=cc3200 --define=__SL__ -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uart_if.obj: G:/My\ Drive/EEC\ 172/cc3200-sdk/example/common/uart_if.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/SpotifyController" --include_path="G:/My Drive/EEC 172/cc3200-sdk/example/common/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/json/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=ccs --define=cc3200 --define=__SL__ -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uart_if.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


