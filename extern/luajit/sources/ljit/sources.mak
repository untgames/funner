SOURCE_FILES := *.c

ifneq (msvc,$(CURRENT_TOOLSET))
GENERATED_SOURCE_FILES := $(LUAJIT_BUILD_INTERNALS_DIR)/lj_vm.s
endif
