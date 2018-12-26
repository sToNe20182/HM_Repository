
FUSIONALG   = project/mt2523_hdk/apps/iot_sdk_demo/src/fusion_algorithm

C_FILES  += $(FUSIONALG)/fusion_alg_interface_api.c    \
            $(FUSIONALG)/fusion_alg_manager.c


CFLAGS  += -I$(SOURCE_DIR)/project/mt2523_hdk/apps/iot_sdk_demo/inc/fusion_algorithm
