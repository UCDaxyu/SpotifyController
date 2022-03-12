################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
HelperFunctions/%.obj: ../HelperFunctions/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -Ooff --include_path="G:/My Drive/EEC 172/Lab_Workspace/SpotifyController" --include_path="G:/My Drive/EEC 172/cc3200-sdk/example/common/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/include" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink/source" --include_path="G:/My Drive/EEC 172/cc3200-sdk/driverlib/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/inc/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/json/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/netapps/" --include_path="G:/My Drive/EEC 172/cc3200-sdk/simplelink_extlib/provisioninglib" --include_path="C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.5.LTS/include" --define=ccs --define=cc3200 --define=__SL__ -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="HelperFunctions/$(basename $(<F)).d_raw" --obj_directory="HelperFunctions" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


