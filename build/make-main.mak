###################################################################################################
#���� ������ "�� ���������"
###################################################################################################
default: build

.PHONY: default

###################################################################################################
#��������� ������
###################################################################################################
COMPONENT_CONFIGURATION_FILE_SHORT_NAME ?= component.mak #������� ��� ����� ������������ ����������
EXPORT_FILE_SHORT_NAME                  ?= export.mak    #������� ��� ����� ��������
PROCESS_DIR_CONFIG_FILE_SHORT_NAME      ?= config.mak    #������� ��� ����� ������������ ��������� ����������
TMP_DIR_SHORT_NAME                      ?= tmp           #������� ��� �������� � ���������� �������
DEFAULT_INSTALLATION_FILES              ?= data/* *.sh   #������ ������, ����� � �������� �����, �������������� �� ���������
DIST_DIR_SHORT_NAME                     ?= dist          #������� ��� �������� � ������������ ������
PCH_SHORT_NAME                          ?= pch.h         #������� ��� PCH �����
SOURCE_FILES_SUFFIXES                   := c cpp         #���������� �������� ������
TOOLSETS_DIR_SHORT_NAME                 := toolsets      #������� ��� �������� � �������������� toolset-��
DOXYGEN_TEMPLATE_DIR_SHORT_NAME         := doxygen       #������� ��� �������� � ��������� doxygen
DOXYGEN_DEFAULT_TOPIC_SHORT_NAME        := default_topic.html #������� ��� �������� �� ��������� doxygen
DOXYGEN_TEMPLATE_CFG_FILE_SHORT_NAME    := template.cfg  #��� ���������� ����� � ������������� doxygen
DOXYGEN_TAGS_DIR_SHORT_NAME             := ~DOXYGEN_TAGS #��� �������� � ������ ������������
EXPORT_VAR_PREFIX                       := export        #������� ����� ���������� ��������������� �������� ����������
BATCH_COMPILE_FLAG_FILE_SHORT_NAME      := batch-flag    #������� ��� �����-����� �������� ����������
PACKAGE_COMMANDS                        := build clean test check run install export info #�������, ������������ ����������� ������
VALID_TARGET_TYPES                      := static-lib dynamic-lib application test-suite package doxygen-info sdk ignore #���������� ���� �����
COMPILE_TOOL                            := tools.c++compile     #��� ������� ������� ���������� C++ ������
LINK_TOOL                               := tools.link           #��� ������� ������� ��������� ������
LIB_TOOL                                := tools.lib            #��� ������� ������� ������������� ��������� ������
INSTALL_TOOL                            := tools.install        #��� ������� ������� ��������� ������ �� ����������
RUN_TOOL                                := tools.run            #��� ������� ������� ������� ����������
DLL_PATH                                := PATH                 #��� ���������� ����� ��� �������� ����� � ���-������
AUTO_COMPILER_DEFINES                   := NAME TYPE LINK_INCLUDES_COMMA COMPILER_CFLAGS EXECUTION_DIR
INSTALLATION_FLAG_SUFFIX                := .installation-flag #������� ����� �����������

###################################################################################################
#����������� �������� ������������
###################################################################################################
BUILD_DIR  := $(dir $(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST)))
USER       ?= $(USERNAME)

-include $(ROOT)/$(USER).settings.mak

###################################################################################################
#����������� ���� � ����������
###################################################################################################
COMPONENT_CONFIGURATION_FILE_SHORT_NAME := $(strip $(COMPONENT_CONFIGURATION_FILE_SHORT_NAME))
EXPORT_FILE_SHORT_NAME                  := $(strip $(EXPORT_FILE_SHORT_NAME))
PROCESS_DIR_CONFIG_FILE_SHORT_NAME      := $(strip $(PROCESS_DIR_CONFIG_FILE_SHORT_NAME))
TMP_DIR_SHORT_NAME                      := $(strip $(TMP_DIR_SHORT_NAME))
SOURCE_FILES_SUFFIXES                   := $(strip $(SOURCE_FILES_SUFFIXES))
TMP_DIR_SHORT_NAME                      := $(strip $(TMP_DIR_SHORT_NAME))
DIST_DIR_SHORT_NAME                     := $(strip $(DIST_DIR_SHORT_NAME))
EXPORT_VAR_PREFIX                       := $(strip $(EXPORT_VAR_PREFIX))
EXPORT_TAR_TMP_FILE_SHORT_NAME          := $(strip $(EXPORT_TAR_TMP_FILE_SHORT_NAME))
EXPORT_EXCLUDE_PATTERN                  := $(strip $(EXPORT_EXCLUDE_PATTERN))
DOXYGEN_TEMPLATE_CFG_FILE_SHORT_NAME    := $(strip $(DOXYGEN_TEMPLATE_CFG_FILE_SHORT_NAME))
DOXYGEN_TEMPLATE_DIR_SHORT_NAME         := $(strip $(DOXYGEN_TEMPLATE_DIR_SHORT_NAME))
DOXYGEN_DEFAULT_TOPIC_SHORT_NAME        := $(strip $(DOXYGEN_DEFAULT_TOPIC_SHORT_NAME))
DEFAULT_INSTALLATION_FILES              := $(strip $(DEFAULT_INSTALLATION_FILES))
INSTALLATION_FLAG_SUFFIX                := $(strip $(INSTALLATION_FLAG_SUFFIX))
CURRENT_TOOLSET                         := $(TOOLSET)
TOOLSETS_DIR                            := $(BUILD_DIR)$(strip $(TOOLSETS_DIR_SHORT_NAME))
TOOLSETS                                := $(patsubst $(TOOLSETS_DIR)/%.mak,%,$(wildcard $(TOOLSETS_DIR)/*.mak))
TOOLSET_FILE                            := $(TOOLSETS_DIR)/$(CURRENT_TOOLSET).mak
DIST_DIR                                := $(ROOT)/$(DIST_DIR_SHORT_NAME)/$(CURRENT_TOOLSET)
DIST_LIB_DIR                            := $(DIST_DIR)/lib
DIST_BIN_DIR                            := $(DIST_DIR)/bin
DIST_INFO_DIR                           := $(DIST_DIR)/doc
PCH_SHORT_NAME                          := $(strip $(PCH_SHORT_NAME))
BATCH_COMPILE_FLAG_FILE_SHORT_NAME      := $(strip $(BATCH_COMPILE_FLAG_FILE_SHORT_NAME))
ROOT_TMP_DIR                            := $(ROOT)/$(TMP_DIR_SHORT_NAME)/$(CURRENT_TOOLSET)
TMP_DIRS                                := $(ROOT_TMP_DIR)
DIST_DIRS                               := $(DIST_LIB_DIR) $(DIST_BIN_DIR) $(DIST_INFO_DIR)
DIRS                                     = $(TMP_DIRS) $(DIST_DIRS)
COMPILE_TOOL                            := $(strip $(COMPILE_TOOL))
LINK_TOOL                               := $(strip $(LINK_TOOL))
LIB_TOOL                                := $(strip $(LIB_TOOL))
INSTALL_TOOL                            := $(strip $(INSTALL_TOOL))
RUN_TOOL                                := $(strip $(RUN_TOOL))
EMPTY                                   := 
SPACE                                   := $(EMPTY) $(EMPTY)
COMMA                                   := ,
EXTERNAL_FILES                          :=
DLL_PATH                                := $(strip $(DLL_PATH))
DOXYGEN_TEMPLATE_DIR                    := $(BUILD_DIR)$(DOXYGEN_TEMPLATE_DIR_SHORT_NAME)
DOXYGEN_TEMPLATE_CFG_FILE               := $(DOXYGEN_TEMPLATE_DIR)/$(DOXYGEN_TEMPLATE_CFG_FILE_SHORT_NAME)
DOXYGEN_DEFAULT_TOPIC                   := $(DOXYGEN_TEMPLATE_DIR)/$(DOXYGEN_DEFAULT_TOPIC_SHORT_NAME)
DOXYGEN_TOOL                            := $(DOXYGEN_DIR)/bin/doxygen
EXPORT_DIR                              ?= $(DIST_DIR)/export
EXPORT_LIB_DIR                          := lib
EXPORT_INCLUDE_DIR                      := include
EXPORT_DLL_DIR                          := bin
EXPORT_BIN_DIR                          := bin
EXPORT_INFO_DIR                         := doc
INSTALLATION_FILES                      := 
INSTALLATION_FLAG                       := $(ROOT_TMP_DIR)/.installation-flag

###################################################################################################
#���� �� ������ ������� - ������������ ��� ���������
###################################################################################################
files ?= %
targets ?= %

###################################################################################################
#�������������� Windows-�����
###################################################################################################
define convert_path
$(subst ; ,;,$(subst \,/,$1))
endef

###################################################################################################
#������� ������ ������ (��� ���������� � ������ �����, ������ ������, ��������)
###################################################################################################
define for_each_file
$(if $2,for $1 in $2; do $3; if [ "$$?" -ne "0" ]; then exit 1; fi; done,true)
endef

###################################################################################################
#����������� ��������� ������ ������
###################################################################################################

#��������� ��������� ���������� (���������������� ��������, ��� �������� ����������, ��� �������������� ����������, ������ � ����� ��� ������� ��������)
define process_subdir
  $$(eval $$(call process_files,$1,$2,*,$3,$4))
endef

#��������� �����(��) (���������������� ��������, ��� ������, ��� �������� ����������, ���/����� ������, ��� �������������� ����������, ������ � ����� ��� ������� ��������)
define process_files_impl
  $2.CONFIG_FILE := $3/$(PROCESS_DIR_CONFIG_FILE_SHORT_NAME)
  
  FILE_LIST :=

  -include $$($2.CONFIG_FILE)  

  ifneq (,$$(filter %*,$4))
    #��������� �������� �����

    $2.SOURCE_INSTALLATION_DIRS := $$(patsubst %/,%,$$(filter %/,$$(wildcard $3$4/)))

    ifeq (,$$(FILE_LIST))
      $2.SOURCE_INSTALLATION_FILES := $$(filter-out %/,$$(wildcard $3$4/))
    else
      $2.SOURCE_INSTALLATION_FILES := $$(FILE_LIST:%=$3%)
    endif
  else
#    ifneq (,$$(filter $3$4/,$$(wildcard $3$4/)))
    ifneq (,$$(wildcard $3$4/*))
      #��������� ����������
      $2.SOURCE_INSTALLATION_DIRS  := $3$4
      $2.SOURCE_INSTALLATION_FILES :=
    else
      $2.SOURCE_INSTALLATION_DIRS :=
      #��������� ������
      ifeq (,$$(FILE_LIST))
        $2.SOURCE_INSTALLATION_FILES := $3$4
      else
        $2.SOURCE_INSTALLATION_FILES := $$(FILE_LIST:%=$3%)
      endif
    endif
  endif      

#��������� ��������
  $$(foreach dir,$$($2.SOURCE_INSTALLATION_DIRS),$$(eval $$(call process_subdir,$1,$$(dir),$5/$$(dir:$3%=%),$6)))
  
  #��������� ������ ������ � ������� ����������
  ifneq (,$$($2.SOURCE_INSTALLATION_FILES))
    $$(eval $$(call $6,$1,$$($2.SOURCE_INSTALLATION_FILES),$5))
  endif
endef

#��������� �����(��) (���������������� ��������, ��� �������� ����������, ���/����� ������, ��� �������������� ����������, ������ � ����� ��� ������� ��������)
define process_files

ifneq (,$5)
  ifneq (,$3)
    $$(foreach file,$3,$$(eval $$(call process_files_impl,$1,process.$$(subst /,-,$$(subst ./,,$$(subst ../,,$$(patsubst %/,%,$2)))),$2/,$$(file),$4,$5)))
  endif
endif

endef

###################################################################################################
#����������� ������
###################################################################################################

#����������� ����� (�������� ����, ������� ����)
define copy_file
  ifeq (,$$(filter $2,$$(FILES_FOR_COPY)))

    FILES_FOR_COPY := $$(FILES_FOR_COPY) $2
    
    $2: $1
			@cp -v "$$<" "$$@"
  endif
endef

#����������� ������ ����� ������� (��� ����, ������ ������, ������� �������)
define copy_files
  $1.COPY_FILES := $$(addprefix $3/,$$(notdir $2))

  DIST_DIRS := $$(DIST_DIRS) $3  

  export: $3 $$($1.COPY_FILES)

  $$(foreach file,$2,$$(eval $$(call copy_file,$$(file),$3/$$(notdir $$(file)))))
endef

#���������� ����������� ������ (��� �����, �������������� �������, ��� ����)
define process_copy_files
  ifneq (,$$(filter %/,$$(wildcard $1/)))
    $$(eval $$(call process_files,$3,$1,*,$2,copy_files))
  else  
    DESTINATION_FILE := $2/$$(notdir $1)       
    DIST_DIRS        := $$(DIST_DIRS) $2

    export: $2 $$(DESTINATION_FILE)

    $$(DESTINATION_FILE): $1
			@cp -v "$$<" "$$@"
  endif    
endef

###################################################################################################
#���������� ��������� ������� / ����������� �����
###################################################################################################
ifneq (,$(filter Win%,$(OS)))

#���������� ��������� ������� (�������, ����@������������, ������, ����, ����)
define ssh_run
plink $(if $4,-P $4) $2 $(if $3,-pw $3,-pw "") $(if $5,-i $5) $1
endef

#����������� ����� �� ��������� ������ (��������, �������, ������, ����, ����)
define ssh_copy
pscp -r -scp -batch $(if $4,-P $4) $(if $3,-pw $3,-pw "") $(if $5,-i $5) $1 $2
endef

else

#���������� ��������� ������� (�������, ����@������������, ������, ����, ����)
define ssh_run
sshpass -p $3 ssh $(if $4,-P $4) $(if $5,-i $5) $2 $1
endef

#����������� ����� �� ��������� ������ (��������, �������, ������, ����, ����)
define ssh_copy
sshpass -p $3 scp -r $(if $4,-P $4) $(if $5,-i $5) $1 $2
endef

endif

###################################################################################################
#����������� ����� ������������ ������ ������
###################################################################################################
ifeq (,$(filter $(CURRENT_TOOLSET),$(TOOLSETS)))
  $(error Unknown toolset '$(CURRENT_TOOLSET)'. Use one of available toolsets '$(TOOLSETS)')
endif

include $(TOOLSET_FILE)

PROFILES := $(sort $(PROFILES))

###################################################################################################
#���������, ��������� �� ������ ������
###################################################################################################
DOXYGEN_TAGS_DIR := $(strip $(ROOT)/$(TMP_DIR_SHORT_NAME)/$(CURRENT_TOOLSET)/$(DOXYGEN_TAGS_DIR_SHORT_NAME))
TMP_DIRS         += $(DOXYGEN_TAGS_DIR)

###################################################################################################
#�������� ������� ��������
###################################################################################################
define check_toolset_constant
  $(if $(filter $1, $(.VARIABLES)),,$(warning Build variable '$1' not defined (check file '$(TOOLSET_FILE)')))
endef

$(call check_toolset_constant,LIB_SUFFIX)
$(call check_toolset_constant,OBJ_SUFFIX)
$(call check_toolset_constant,DLL_SUFFIX)
$(call check_toolset_constant,EXE_SUFFIX)
$(call check_toolset_constant,DLL_PREFIX)

###################################################################################################
#����������� ������ ������������ ���������� � ������ ��������
###################################################################################################
COMPONENT_CONFIGURATION_FILE := $(firstword $(wildcard $(filter %$(COMPONENT_CONFIGURATION_FILE_SHORT_NAME), $(MAKEFILE_LIST:makefile=$(COMPONENT_CONFIGURATION_FILE_SHORT_NAME)))))
EXPORT_FILES                 := $(wildcard $(filter %$(EXPORT_FILE_SHORT_NAME), $(MAKEFILE_LIST:makefile=$(EXPORT_FILE_SHORT_NAME))))
COMPONENT_DIR                := $(dir $(COMPONENT_CONFIGURATION_FILE))

ifeq (,$(COMPONENT_CONFIGURATION_FILE))
  $(error Configuration file '$(COMPONENT_CONFIGURATION_FILE_SHORT_NAME)' not found at project tree (root='$(ROOT)'))
endif

include $(COMPONENT_CONFIGURATION_FILE)

###################################################################################################
#�������� �������������� �������� (���� ��������)
###################################################################################################
define load_exports
#�������� ������� �����
ifeq (,$$(wildcard $1))
  $$(error Export file '$1' not found)
endif

#������� ���������� $(EXPORT_VAR_PREFIX).*
  OLD_VARIABLES  := $$(filter $(EXPORT_VAR_PREFIX).%,$$(.VARIABLES))
  COMPONENT_DIRS :=

#����������� ����� �����������
  include $1

#��������� ��������
  EXPORT_VARIABLES       := $$(filter-out $$(OLD_VARIABLES),$$(filter $(EXPORT_VAR_PREFIX).%,$$(.VARIABLES)))
  EXPORT_COMPONENT_NAMES := $$(patsubst $(EXPORT_VAR_PREFIX).%,%,$$(foreach var,$$(EXPORT_VARIABLES),$$(var:%.$$(word $$(words $$(subst .,$(SPACE),$$(var))),$$(subst .,$(SPACE),$$(var)))=%)))

# ���������� ����� � �����������
  $$(foreach name,$$(EXPORT_COMPONENT_NAMES),$$(eval paths.$$(name) := $$(dir $1)))

  $$(foreach dir,$$(COMPONENT_DIRS),$$(eval $$(call load_exports,$$(dir $1)$$(dir)/$(EXPORT_FILE_SHORT_NAME))))
endef

$(foreach file,$(EXPORT_FILES),$(eval $(call load_exports,$(file))))
#$(foreach var,$(sort $(filter export.%,$(.VARIABLES))),$(warning $(var)=$($(var))))
#$(foreach path,$(sort $(filter paths.%,$(.VARIABLES))),$(warning $(path)=$($(path))))

###################################################################################################
#������������� ����
###################################################################################################
define specialize_paths
$(foreach dir,$(strip $1),$(if $(filter /%,$(dir)),$(dir),$(COMPONENT_DIR)$(dir)))
endef

###################################################################################################
#�������������� ����� make � ��������� ����� (��� ����)
###################################################################################################
ifneq (,$(filter Win%,$(OS)))

define get_system_dir
cmd "\\/C" "cd $1 && cd"
endef

else

define get_system_dir
cd "$1" && pwd
endef

endif

###################################################################################################
#���������� � ������� ���������� (������� ������� ����������, ������ ��������� � ������������� ������������)
###################################################################################################
define prepare_to_execute
export PATH="$(subst ;,:,$(call convert_path,$(CURDIR)/$(DIST_BIN_DIR);$(foreach dir,$(ADDITIONAL_PATHS),$(dir);)$$PATH))" \
$(DLL_PATH)="$(subst ;,:,$(call convert_path,$(foreach dir,$2,$(CURDIR)/$(dir);)$$$(DLL_PATH)))" \
BIN_DIR=$(DIST_BIN_DIR) \
 && cd "$1"
endef

###################################################################################################
#��������� ����� ����������
###################################################################################################

#�������� ����������� ���������� ����� �� ����-����� �������� ���������� (��� ��������� �����, ��������� �������, ����-����)
define create_object_file_dependency
$2/$$(notdir $$(basename $1))$(OBJ_SUFFIX): $1 $3
	@
endef

#������������ ������� ��������� �������� ������ � �����. �� ��������� (������ �������� ������, ��������� �������)
define test_source_and_object_files
$(foreach src,$1,if [ $(src) -nt $2/$(notdir $(basename $(src)))$(OBJ_SUFFIX) ]; then echo $(src); fi &&) true 
endef

#������� �������� ���������� (��� ����, ��� ������)
define batch-compile
  $2.FLAG_FILE        := $$($2.TMP_DIR)/$$(BATCH_COMPILE_FLAG_FILE_SHORT_NAME)
  $1.FLAG_FILES       := $$($1.FLAG_FILES) $$($2.FLAG_FILE)
  $2.COMPILER_DEFINES := $$(strip $$($1.COMPILER_DEFINES))# $$(foreach var,$$(AUTO_COMPILER_DEFINES),MAKE_TARGET_$$(var)='$$(subst $$(SPACE),%,$$(strip $$($1.$$(var))))')
  
  ifneq (,$$(strip $$($2.PCH)))
  
  $$($2.FLAG_FILE): $$($2.PCH_OUTPUT)
  
  endif  

  ifeq (,$$(wildcard $$($2.FLAG_FILE).incomplete-build))  

    $$($2.FLAG_FILE): $$($2.SOURCE_FILES)
			@echo build-start > $$@.incomplete-build
			@$$(call $$(if $$($1.COMPILE_TOOL),$$($1.COMPILE_TOOL),$(COMPILE_TOOL)),$$(sort $$(filter-out force,$$?)),$$($2.SOURCE_DIR) $$($1.INCLUDE_DIRS),$$($1.INCLUDE_FILES),$$($2.TMP_DIR),$$($2.COMPILER_DEFINES),$$($1.COMPILER_CFLAGS),$$($2.PCH),$$($1.DLL_DIRS))
			@echo batch-flag-file > $$@
			@$(RM) $$@.incomplete-build

  else  #� ������ ���� ������ ���� �� ���������
  
    $$($2.FLAG_FILE): $2.UPDATED_SOURCE_FILES := $$(shell $$(call test_source_and_object_files,$$($2.SOURCE_FILES),$$($2.TMP_DIR)))
  
    $$($2.FLAG_FILE): $$($2.SOURCE_FILES)
			@$$(if $$($2.UPDATED_SOURCE_FILES),$$(call $$(if $$($1.COMPILE_TOOL),$$($1.COMPILE_TOOL),$(COMPILE_TOOL)),$$(sort $$($2.UPDATED_SOURCE_FILES)),$$($2.SOURCE_DIR) $$($1.INCLUDE_DIRS),$$($1.INCLUDE_FILES),$$($2.TMP_DIR),$$($2.COMPILER_DEFINES),$$($1.COMPILER_CFLAGS),$$($2.PCH),$$($1.DLL_DIRS)))
			@echo batch-flag-file > $$@
			@$(RM) $$@.incomplete-build

  endif  

  ifneq (,$$($2.NEW_SOURCE_FILES))
    $$($2.FLAG_FILE): force
  endif
  
  $$(foreach source,$$($2.SOURCE_FILES),$$(eval $$(call create_object_file_dependency,$$(source),$$($2.TMP_DIR),$$($2.FLAG_FILE))))
endef

#��������� �������� � ��������� ������� (��� ����, ���� � �������� � ��������� �������, ������ ����������� ��������)
define process_source_dir
  ifeq (,$$(wildcard $2))
    $$(error Source dir '$2' not found at build target '$1' component-dir='$(COMPONENT_DIR)')
  endif

  MODULE_PATH := $$(subst ./,,$$(subst ../,,$2))
  MODULE_NAME := $1.$$(subst /,-,$$(MODULE_PATH))
  
  ifneq (,$$(wildcard $2/sources.mak))
    SOURCE_FILES :=

    GENERATED_SOURCE_FILES :=
    
    $$(foreach profile,$(PROFILES),$$(eval SOURCE_FILES.$$(profile) :=))      
  
    include $2/sources.mak    
    
    $$(foreach profile,$(PROFILES),$$(eval $$(MODULE_NAME).SOURCE_FILES := $$($$(MODULE_NAME).SOURCE_FILES) $$(SOURCE_FILES.$$(profile))))        

    $$(MODULE_NAME).SOURCE_FILES := $$(wildcard $$(SOURCE_FILES:%=$2/%)) $$(wildcard $$($$(MODULE_NAME).SOURCE_FILES:%=$2/%)) $$(GENERATED_SOURCE_FILES)
  else
    $$(MODULE_NAME).SOURCE_FILES := $$(wildcard $$(SOURCE_FILES_SUFFIXES:%=$2/*.%))
  endif  
  
  $1.SOURCE_FILES            := $$($1.SOURCE_FILES) $$($$(MODULE_NAME).SOURCE_FILES)
  $$(MODULE_NAME).SOURCE_DIR := $2
  $$(MODULE_NAME).TMP_DIR    := $$($1.TMP_DIR)/$$(MODULE_PATH)
  $1.TMP_DIRS                := $$($$(MODULE_NAME).TMP_DIR) $$($1.TMP_DIRS)  
  $1.INSTALLATION_FILES      := $$($1.INSTALLATION_FILES) $$(foreach file,$(DEFAULT_INSTALLATION_FILES),$$(wildcard $2/$$(file)))
  
#����������  
 
  $$(foreach macros,$(SOURCE_PROCESS_MACROSES),$$(eval $$(call $$(macros),$1,$$(MODULE_NAME))))  

  ifneq (,$$($$(MODULE_NAME).SOURCE_FILES))
    $$(MODULE_NAME).OBJECT_FILES := $$(patsubst %,$$($$(MODULE_NAME).TMP_DIR)/%$(OBJ_SUFFIX),$$(notdir $$(basename $$($$(MODULE_NAME).SOURCE_FILES))))
    $$(MODULE_NAME).PCH          := $$(if $$(wildcard $2/$(PCH_SHORT_NAME)),$(PCH_SHORT_NAME))
    $1.OBJECT_FILES              := $$($1.OBJECT_FILES) $$($$(MODULE_NAME).OBJECT_FILES)    
    
    $$(eval $$(call batch-compile,$1,$$(MODULE_NAME)))
  endif

  $$(foreach macros,$3,$$(eval $$(call $$(macros),$1,$$(MODULE_NAME))))    
endef

#�������� ����������� ��� ����������� ������� ������ (��� �������� �����, �������� ������)
define create_extern_file_dependency
  ifeq (,$$(filter $1,$$(EXTERNAL_FILES)))
    DEPENDENCY_SOURCE := $$(firstword $$(wildcard $$(patsubst %,%/$$(notdir $1),$2)))
  
    ifeq (,$$(strip $$(DEPENDENCY_SOURCE)))
      DEPENDENCY_SOURCE := $(DIST_BIN_DIR)/$$(notdir $1)
    endif

    ifneq ($$(strip $1),$$(strip $$(DEPENDENCY_SOURCE)))

      $1: $$(DEPENDENCY_SOURCE)
				@cp -fv $$< $$@
				@chmod ug+rwx $$@

    endif
    
    EXTERNAL_FILES := $$(EXTERNAL_FILES) $1
  endif  
endef

#��������� ������ ������ � ���������� (������ ������)
define get_file_list_with_dirs
$(foreach file,$1,$(if $(filter ./,$(dir $(file))),./$(file),$(file)))
endef

#��������� ������ ������ ��� ���������� �������� (������ ������, �������)
define select_files_for_dir
$(foreach file,$(call get_file_list_with_dirs,$1),$(if $(filter $2,$(dir $(file))),$(file) ))
endef

#���������� ������� ����������� (������ ������)
define build_installation_command
$(foreach dir,$(sort $(dir $(call get_file_list_with_dirs,$1))),$(call $(INSTALL_TOOL),$(call select_files_for_dir,$1,$(dir)),$(dir)) && ) true
endef

#����� ��� ����� � ��������� ������� (��� ����, ������ �������� ����������� ��� ��������� ��������� � ��������� �������)
define process_target_with_sources
#���������� ��������� �� ���������
  $$(foreach lib,$$($1.EXCLUDE_DEFAULT_LIBS),$$(eval $1.LIBS := $$(filter-out $$(lib),$$($1.LIBS))))  

  $1.TMP_DIR             := $(ROOT)/$(TMP_DIR_SHORT_NAME)/$(CURRENT_TOOLSET)/$1
  $1.TMP_DIRS            := $$($1.TMP_DIR)
  $1.INCLUDE_DIRS        := $$(call specialize_paths,$$($1.INCLUDE_DIRS))
  $1.SOURCE_DIRS         := $$(call specialize_paths,$$($1.SOURCE_DIRS))
  $1.OBJECT_FILES        := $$(call specialize_paths,$$($1.OBJECT_FILES))
  $1.DOCUMENTATION_DIRS  := $$(call specialize_paths,$$($1.DOCUMENTATION_DIRS))
  $1.LIB_DIRS            := $$(call specialize_paths,$$($1.LIB_DIRS)) $(DIST_LIB_DIR)
  $1.DLL_DIRS            := $$(call specialize_paths,$$($1.DLL_DIRS)) $(DIST_BIN_DIR)
  $1.EXECUTION_DIR       := $$(strip $$($1.EXECUTION_DIR))
  $1.EXECUTION_DIR       := $$(if $$($1.EXECUTION_DIR),$(COMPONENT_DIR)$$($1.EXECUTION_DIR))
  $1.LIBS                := $$($1.LIBS:%=$(LIB_PREFIX)%$(LIB_SUFFIX))
  $1.LIB_DEPS            := $$(filter $$(addprefix %/,$$($1.LIBS)),$$(wildcard $$($1.LIB_DIRS:%=%/*)))  
  $1.LINK_INCLUDES_COMMA := $$(subst $$(SPACE),$$(COMMA),$$(strip $$($1.LINK_INCLUDES)))  

  $$(foreach dir,$$($1.SOURCE_DIRS),$$(eval $$(call process_source_dir,$1,$$(dir),$2)))

  TMP_DIRS := $$($1.TMP_DIRS) $$(TMP_DIRS)
  TMP_CLEAN_DIRS := $(TMP_CLEAN_DIRS) $(ROOT)/$(TMP_DIR_SHORT_NAME)/$(CURRENT_TOOLSET)/$1

  build: $$($1.TARGET_DLLS)  

  $$(foreach file,$$($1.TARGET_DLLS),$$(eval $$(call create_extern_file_dependency,$$(file),$$($1.DLL_DIRS))))  
  
#����������� 
  $1.INSTALLATION_FILES := $$($1.INSTALLATION_FILES) $$(foreach file,$(DEFAULT_INSTALLATION_FILES),$$(wildcard $$(COMPONENT_DIR)$$(file))) $$($1.TARGET_DLLS)  
  $1.INSTALLATION_FLAG  := $$($1.TMP_DIR)/$(INSTALLATION_FLAG_SUFFIX)
  INSTALLATION_FILES    := $$(INSTALLATION_FILES) $$($1.INSTALLATION_FILES)
  INSTALLATION_FLAGS    := $$(INSTALLATION_FLAGS) $$($1.INSTALLATION_FLAG)
  
  $$($1.INSTALLATION_FLAG): $$($1.INSTALLATION_FILES)
		@touch $$@
endef

#������������� ����
define process_target.ignore
endef

#��������� ���� static-lib (��� ����)
define process_target.static-lib
  $1.NAME := $$(strip $$($1.NAME))
  
  ifeq (,$$($1.NAME))
    $$(error Empty static name at build target '$1' component-dir='$(COMPONENT_DIR)')
  endif

  $1.LIB_FILE                      := $(DIST_LIB_DIR)/$(LIB_PREFIX)$$($1.NAME)$(LIB_SUFFIX)
  TARGET_FILES                     := $$(TARGET_FILES) $$($1.LIB_FILE)
  $1.SOURCE_INSTALLATION_LIB_FILES := $$($1.LIB_FILE)

  build: $$($1.LIB_FILE)

  $$(eval $$(call process_target_with_sources,$1))  

  $$($1.LIB_FILE): $$($1.FLAG_FILES) $$($1.OBJECT_FILES)
		@echo Create library $$(notdir $$@)...
		@$$(call $$(if $$($1.LIB_TOOL),$$($1.LIB_TOOL),$(LIB_TOOL)),$$@,$$($1.OBJECT_FILES))
endef

#��������� ���� dynamic-lib (��� ����)
define process_target.dynamic-lib
  $1.NAME := $$(strip $$($1.NAME))
  
  ifeq (,$$($1.NAME))
    $$(error Empty dynamic library name at build target '$1' component-dir='$(COMPONENT_DIR)')
  endif
  
  $1.DLL_FILE                      := $(DIST_BIN_DIR)/$(DLL_PREFIX)$$($1.NAME)$(DLL_SUFFIX)
  $1.LIB_FILE                      := $(DIST_LIB_DIR)/$(LIB_PREFIX)$$(notdir $$(basename $$($1.DLL_FILE)))$(DLL_LIB_SUFFIX)
  $1.DEF_FILE                      := $$(call specialize_paths,$$($1.DEF_FILE))
  $1.LIB_TMP_FILE                  := $$(dir $$($1.DLL_FILE))$(LIB_PREFIX)$$(notdir $$(basename $$($1.DLL_FILE)))$(DLL_LIB_SUFFIX)
  TARGET_FILES                     := $$(TARGET_FILES) $$($1.DLL_FILE) $$($1.LIB_FILE)
  $1.TARGET_DLLS                   := $$($1.DLLS:%=$(DIST_BIN_DIR)/$(DLL_PREFIX)%$(DLL_SUFFIX))
  DIST_DIRS                        := $$(DIST_DIRS) $$(dir $$($1.DLL_FILE))
  $1.SOURCE_INSTALLATION_DLL_FILES := $$($1.TARGET_DLLS) $$($1.DLL_FILE)
  $1.SOURCE_INSTALLATION_LIB_FILES := $$($1.LIB_FILE)  

  build: $$($1.DLL_FILE) $$($1.LIB_FILE)

  $$(eval $$(call process_target_with_sources,$1))
  
  $$($1.LIB_FILE): $$($1.DLL_FILE)

  $$($1.DLL_FILE): $$($1.FLAG_FILES) $$($1.LIB_DEPS) $$($1.OBJECT_FILES) $$($1.DEF_FILE)
		@echo Create dynamic library $$(notdir $$($1.DLL_FILE))...
		@$$(call $$(if $$($1.LINK_TOOL),$$($1.LINK_TOOL),$(LINK_TOOL)),$$($1.DLL_FILE),$$($1.OBJECT_FILES) $$($1.LIBS),$$($1.LIB_DIRS),$$($1.LINK_INCLUDES),$$($1.LINK_FLAGS),$$($1.DEF_FILE))
		@$(RM) $$(basename $$($1.DLL_FILE)).exp
		@if [ -e $$($1.LIB_TMP_FILE) ]; then mv -f $$($1.LIB_TMP_FILE) $(DIST_LIB_DIR); fi
endef

#��������� ���� application (��� ����)
define process_target.application
  $1.NAME := $$(strip $$($1.NAME))
  
  ifeq (,$$($1.NAME))
    $$(error Empty application name at build target '$1' component-dir='$(COMPONENT_DIR)')
  endif

  $1.OUT_DIR                       := $$(if $$($1.OUT_DIR),$$(COMPONENT_DIR)/$$($1.OUT_DIR),$$(DIST_BIN_DIR))
  $1.EXE_FILE                      := $$($1.OUT_DIR)/$$($1.NAME)$$(if $$(suffix $$($1.NAME)),,$(EXE_SUFFIX))
  TARGET_FILES                     := $$(TARGET_FILES) $$($1.EXE_FILE)
  $1.TARGET_DLLS                   := $$($1.DLLS:%=$$($1.OUT_DIR)/$(DLL_PREFIX)%$(DLL_SUFFIX))  
  DIST_DIRS                        := $$(DIST_DIRS) $$(dir $$($1.EXE_FILE))
  $1.SOURCE_INSTALLATION_DLL_FILES := $$($1.TARGET_DLLS)
  $1.SOURCE_INSTALLATION_EXE_FILES := $$($1.EXE_FILE)
  $1.INSTALLATION_FILES            := $$($1.INSTALLATION_FILES) $$($1.EXE_FILE) 

  build: $$($1.EXE_FILE)

  $$(eval $$(call process_target_with_sources,$1))
  
  ifeq (,$$($1.EXECUTION_DIR))
    $1.EXECUTION_DIR := $$($1.OUT_DIR)
  endif
  
  $$($1.EXE_FILE): $$($1.FLAG_FILES) $$($1.LIB_DEPS) $$($1.OBJECT_FILES)
		@echo Linking $$(notdir $$@)...
		@$$(call $$(if $$($1.LINK_TOOL),$$($1.LINK_TOOL),$(LINK_TOOL)),$$@,$$($1.OBJECT_FILES) $$($1.LIBS),$$($1.LIB_DIRS),$$($1.LINK_INCLUDES),$$($1.LINK_FLAGS))

  RUN.$1: $$($1.EXE_FILE)
		@echo Running $$(notdir $$<)...
		@$$(call $$(if $$($1.RUN_TOOL),$$($1.RUN_TOOL),$(RUN_TOOL)),$$(patsubst %,"$(CURDIR)/%",$$<) $(args),$$($1.EXECUTION_DIR),$$(dir $$($1.EXE_FILE)) $$($1.DLL_DIRS),$$($1.TARGET_DLLS)) > $$@

  ifneq (,$$(filter $$(files:%=$$($1.OUT_DIR)/%$(EXE_SUFFIX)),$$($1.EXE_FILE)))
    ifeq (,$$($1.DISABLE_RUN))
      run: RUN.$1
    endif
  endif
endef

#����� ����� (��� ����, ��� ������, ��� �����)
define process_tests_source_dir_run_test
  TEST_MODULE.$2::
		@$$(call $$(if $$($1.RUN_TOOL),$$($1.RUN_TOOL),$(RUN_TOOL)),$3 $(args),$$($2.EXECUTION_DIR),$$($2.TARGET_DIR) $$($1.DLL_DIRS),$$($1.TARGET_DLLS))

endef

#��������� �������� � ��������� ������� ������ (��� ����, ��� ������)
define process_tests_source_dir
  ifeq (,$$($1.TARGET_DIR))
    $2.TARGET_DIR := $$($2.TMP_DIR)
  else
    $2.TARGET_DIR := $$($1.TARGET_DIR)
  endif

  $2.TEST_EXE_FILES     := $$(filter $$(files:%=$$($2.TARGET_DIR)/%$(EXE_SUFFIX)),$$(patsubst $$($2.TMP_DIR)/%$(OBJ_SUFFIX),$$($2.TARGET_DIR)/%$(EXE_SUFFIX),$$($2.OBJECT_FILES)))
  $2.TEST_RESULT_FILES  := $$(patsubst $$($2.SOURCE_DIR)/%,$$($2.TMP_DIR)/%,$$(wildcard $$($2.SOURCE_DIR)/*.result))
  $2.EXECUTION_DIR      := $$(if $$($1.EXECUTION_DIR),$$($1.EXECUTION_DIR),$$($2.SOURCE_DIR))
  $1.TARGET_DLLS        := $$($1.TARGET_DLLS) $$($1.DLLS:%=$$($2.TARGET_DIR)/$(DLL_PREFIX)%$(DLL_SUFFIX))
  $2.USED_APPLICATIONS  := $$($1.USED_APPLICATIONS:%=$$(DIST_BIN_DIR)/%$(EXE_SUFFIX))
  $2.RUN_FILES          := $$(filter $$(files:%=$$($2.SOURCE_DIR)/%.sh),$$(wildcard $$($2.SOURCE_DIR)/*.sh)) $$(filter $$(files:%=$$($2.TARGET_DIR)/%$(EXE_SUFFIX)),$$($2.TEST_EXE_FILES))

  build: $$($2.TEST_EXE_FILES)
  test: TEST_MODULE.$2
  check: CHECK_MODULE.$2
  .PHONY: TEST_MODULE.$2 CHECK_MODULE.$2
  
#�����������
  $1.INSTALLATION_FILES := $$($1.INSTALLATION_FILES) $$($2.TEST_EXE_FILES)
  
#������� ������ �����
  $$($2.TARGET_DIR)/%$(EXE_SUFFIX): $$($2.TMP_DIR)/%$(OBJ_SUFFIX) $$($1.LIB_DEPS)
		@echo Linking $$(notdir $$@)...
		@$$(call $$(if $$($1.LINK_TOOL),$$($1.LINK_TOOL),$(LINK_TOOL)),$$@,$$(filter %$(OBJ_SUFFIX),$$<) $$($1.LIBS),$$($1.LIB_DIRS),$$($1.LINK_INCLUDES),$$($1.LINK_FLAGS))

#������� ��������� �����-���������� ������������
  $$($2.TMP_DIR)/%.result: $$($2.TARGET_DIR)/%$(EXE_SUFFIX)
		@echo Running $$(notdir $$<)...
		@$$(call $$(if $$($1.RUN_TOOL),$$($1.RUN_TOOL),$(RUN_TOOL)),$$< $(args),$$($2.EXECUTION_DIR),$$($2.TARGET_DIR) $$($1.DLL_DIRS),$$($1.TARGET_DLLS)) > $(CURDIR)/$$@
		
#������� ��������� �����-���������� ������������ �� shell-�����
  $$($2.SOURCE_DIR)/%.sh: $$($2.TEST_EXE_FILES)
  
  $$($2.TMP_DIR)/%.result: $$($2.SOURCE_DIR)/%.sh $$($2.USED_APPLICATIONS)
		@echo Running $$(notdir $$<)...
		@$$(call $$(if $$($1.RUN_TOOL),$$($1.RUN_TOOL),$(RUN_TOOL)),$$< $(args),$$($2.EXECUTION_DIR),$$($2.TARGET_DIR) $$($1.DLL_DIRS),$$($1.TARGET_DLLS)) > $(CURDIR)/$$@

#������� ������� ������
  $$(foreach file,$$($2.RUN_FILES),$$(eval $$(call process_tests_source_dir_run_test,$1,$2,$$(file))))      

#������� �������� ����������� ������������
  CHECK_MODULE.$2: $$($2.TEST_RESULT_FILES)
		@echo Checking results of module '$2'...
		@$$(call for_each_file,file,$$(notdir $$(filter $$(files:%=$$($2.TMP_DIR)/%.result),$$^)),diff --strip-trailing-cr --context=1 $$($2.SOURCE_DIR)/$$$$file $$($2.TMP_DIR)/$$$$file)
endef

#��������� ���� test-suite (��� ����)
define process_target.test-suite
  $$(eval $$(call process_target_with_sources,$1,process_tests_source_dir))
  
  build: $$($1.FLAG_FILES)
endef

#��������� ����������� ������ (��� ������, ������� make)
define process_package_components
  $2: PACKAGE_$2.$1

  .PHONY: PACKAGE_$2.$1

  PACKAGE_$2.$1:
		@$$(foreach component,$$($1.COMPONENTS),$(MAKE) -C $$(subst :, ,$(COMPONENT_DIR)/$$(component)) $2 && ) true
endef

#��������� ���� package (��� ����)
define process_target.package
  ifneq (,$$($1.COMPONENTS))
    $$(foreach command,$(PACKAGE_COMMANDS),$$(eval $$(call process_package_components,$1,$$(command))))
  else
    $$(warning Empty package at build target '$1' component-dir='$(COMPONENT_DIR)')
  endif  
endef

#��������� ���� ������������ ������������(��� ����)
define process_target.doxygen-info 
  $1.TMP_DIR               := $(ROOT)/$(TMP_DIR_SHORT_NAME)/$(CURRENT_TOOLSET)/$1
  $1.SOURCE_DIRS           := $$(call specialize_paths,$$($1.SOURCE_DIRS))
  $1.DOXYGEN_CFG_FILE      := $$($1.TMP_DIR)/doxygen.cfg
  $1.DOXYGEN_TAG_FILE      := $(DOXYGEN_TAGS_DIR)/$1.tag
  $1.DOXYGEN_CHM_FILE      := $$(DIST_INFO_DIR)/$$($1.CHM_NAME).chm
  $1.DOXYGEN_SELF_CHM_FILE := $$(if $$(strip $$($1.IMPORT_CHM)),$$($1.TMP_DIR)/index.chm,$$($1.DOXYGEN_CHM_FILE))
  $1.IMPORT_CHM            := $$($1.IMPORT_CHM:%=$$(DIST_INFO_DIR)/%.chm)
  TMP_DIRS                 := $$($1.TMP_DIR) $$(TMP_DIRS)
  TMP_CLEAN_DIRS           := $(TMP_CLEAN_DIRS) $(ROOT)/$(TMP_DIR_SHORT_NAME)/$(CURRENT_TOOLSET)/$1 $$($1.DOXYGEN_TAG_FILE) 

  info: INFO.$1

  .PHONY: INFO.$1

  INFO.$1: $$($1.DOXYGEN_CHM_FILE)  

ifneq (,$$($1.SOURCE_DIRS))  

  #�������� ������� ���������� � ���� � ������� ���������������� ����

  ifneq (,$$(filter info,$$(MAKECMDGOALS)))
    ifeq (,$(DOXYGEN_DIR))
      $$(error Documentation tool not found (DOXYGEN_DIR not defined))
    endif
  endif

  $$($1.DOXYGEN_SELF_CHM_FILE): $(DOXYGEN_TAGS_DIR) $$(DIST_INFO_DIR) $$($1.TMP_DIR) $$($1.DOXYGEN_CFG_FILE)
		@echo Generate $$(notdir $$@)...
		@export PATH="$$(subst ;,:,$$(call convert_path,$(CURDIR)/$(DIST_BIN_DIR);$$(HHC_DIR);)$$(PATH)))" && "$$(DOXYGEN_TOOL)" $$($1.DOXYGEN_CFG_FILE)
		@cp "$$($1.TMP_DIR)/html/index.chm" "$$@"

  $$($1.DOXYGEN_CFG_FILE): $$($1.TMP_DIR) force  
		@cp "$$(DOXYGEN_TEMPLATE_CFG_FILE)" "$$@"
		@echo "OUTPUT_DIRECTORY = $$($1.TMP_DIR)" >> "$$@"
		@echo "INCLUDE_PATH = $$($1.INCLUDE_DIRS)" >> "$$@"
		@echo "INPUT = $$($1.SOURCE_DIRS)" >> "$$@"
		@echo "GENERATE_TAGFILE =  $$($1.DOXYGEN_TAG_FILE)" >> "$$@"
		@echo 'HHC_LOCATION = "$(HHC_DIR)/hhc"' >> "$$@"
		@echo TAGFILES = `cd $(DOXYGEN_TAGS_DIR) && for file in $$$$(ls); do if [ $(DOXYGEN_TAGS_DIR)/$$$$file != $$($1.DOXYGEN_TAG_FILE) ]; then echo $(DOXYGEN_TAGS_DIR)/$$$$file=../../../$$$$(basename $$$$file .tag)/html; fi; done` >> "$$@"
		
  $1.IMPORT_CHM := $$($1.IMPORT_CHM) $$($1.DOXYGEN_SELF_CHM_FILE)

endif
  
ifneq ($$($1.DOXYGEN_CHM_FILE),$$($1.DOXYGEN_SELF_CHM_FILE))

ifeq (,$$(HHC_DIR))
    $$(error 'Microsoft Help Workshop not found (set environment variable HHC_DIR to its directory)')
endif

  $1.MERGE_HHP         := $$($1.TMP_DIR)/merge.hhp
  $1.MERGE_HHC         := $$($1.TMP_DIR)/index.hhc
  $1.MERGE_HHK         := $$($1.TMP_DIR)/index.hhk
  $1.DEFAULT_TOPIC     := $$(call specialize_paths,$$($1.DEFAULT_TOPIC))
  $1.DEFAULT_TOPIC     := $$(if $$(wildcard $$($1.DEFAULT_TOPIC)),$$($1.DEFAULT_TOPIC),$$(DOXYGEN_DEFAULT_TOPIC))
	$1.DST_DEFAULT_TOPIC := $$($1.TMP_DIR)/default_topic.html
	$1.DST_IMPORT_CHM    := $$($1.IMPORT_CHM:$$(DIST_INFO_DIR)/%=$$($1.TMP_DIR)/%)  
  
  $$($1.DST_DEFAULT_TOPIC): $$($1.DEFAULT_TOPIC)
		@cp "$$<" "$$@"

  $$($1.TMP_DIR)/%.chm: $$(DIST_INFO_DIR)/%.chm
		@cp "$$<" "$$@"

  $$($1.MERGE_HHC): force
		@echo "<html><body>" > "$$@"
		@echo '<object type="text/site properties"><param name="FrameName" value="right"><param name="Window Styles" value="0x800025"></object>' >> "$$@"
		@$$(foreach file,$$($1.IMPORT_CHM),echo '<ul>' >> "$$@" && echo '<li><object type="text/sitemap"><param name="Name" value="$$(basename $$(notdir $$(file)))"><param name="Local" value="default_topic.html"></object>'  >> "$$@" && echo '<li>' >> "$$@" && echo '<object type="text/sitemap">' >> "$$@" && echo '<param name="Merge" value="$$(notdir $$(file))::\index.hhc">' >> "$$@" && echo '</object>' >>"$$@" && echo '</ul>' >> "$$@" && ) true
		@echo "</body></html>" >> "$$@"

  $$($1.MERGE_HHK): force
		@echo "<html><body>" > "$$@"
		@echo '<object type="text/site properties"><param name="FrameName" value="right">' >> "$$@" && echo '</object>' >> "$$@"
		@echo '<ul>' >> "$$@" && echo '<li> <object type="text/sitemap"><param name="Name" value="default">' >> "$$@" && echo '<param name="Local" value="default_topic.html">' >> "$$@"
		@echo "</object>" >> "$$@" && echo "</ul></body></html>" >> "$$@"

  $$($1.MERGE_HHP): force
		@echo "[OPTIONS]" > "$$@"
		@echo "Auto Index=Yes" >> "$$@"
		@echo "Binary Index=Yes" >> "$$@"
		@echo "Compatibility=1.1" >> "$$@"
		@echo "Compiled file=merged.chm" >> "$$@"
		@echo "Contents file=index.hhc" >> "$$@"
		@echo "Default Window=TP" >> "$$@"
		@echo "Default topic=default_topic.html" >> "$$@"
		@echo "Error log file=error_log.txt" >> "$$@"
		@echo "Full-text search=Yes" >> "$$@"
		@echo "Index file=index.hhk" >> "$$@"
		@echo "Language=0x409 English (United States)" >> "$$@"
		@echo "Title=Master" >> "$$@"
		@echo "[WINDOWS]" >> "$$@"		
		@echo 'TP=,"index.hhc","index.hhk","default_topic.html","default_topic.html",,,,,0x63520,222,0x304e,[0,0,879,615],0xb0000,,,,,,0' >> "$$@"
		@echo "[MERGE FILES]" >> "$$@"
		@$$(foreach file,$$($1.IMPORT_CHM),echo $$(notdir $$(file)) >> "$$@" && ) true
		@echo "[FILES]" >> "$$@"
		@echo default_topic.html >> "$$@"

  $$($1.DOXYGEN_CHM_FILE): $$($1.IMPORT_CHM) $$($1.TMP_DIR) $$($1.DST_DEFAULT_TOPIC) $$($1.DST_IMPORT_CHM) $$($1.MERGE_HHP) $$($1.MERGE_HHK) $$($1.MERGE_HHC)
		@echo Merging $$(notdir $$@)...
ifeq ($$($1.DEFAULT_TOPIC),$$(DOXYGEN_DEFAULT_TOPIC))
		@echo Default topic for doxygen documentation merge not defined. Using default (set target property DEFAULT_TOPIC for use custom default topic page)
endif
		@"$$(HHC_DIR)/hhc" $$($1.MERGE_HHP) || true
		@mv $$($1.TMP_DIR)/merged.chm "$$@"

endif
  
endef

#������ SDK (��� ����)
define process_target.sdk
  $1.EXPORT.LIBS               := $$($1.LIBS)
  $1.EXPORT.LIB_DIRS           := $$($1.LIB_DIRS) $$(DIST_LIB_DIR)
  $1.EXPORT.INCLUDES           := $$($1.INCLUDE_DIRS)
  $1.EXPORT.DLLS               := $$($1.DLLS)
  $1.EXPORT.EXECUTABLES        := $$($1.EXECUTABLES)
  $1.EXPORT.CHMS               := $$($1.CHMS)  
  $1.EXPORT.LIB_FILTER         := $$(strip $$($1.LIB_FILTER))
  $1.EXPORT.LIB_EXCLUDE_FILTER := $$($1.LIB_EXCLUDE_FILTER)  
  $1.EXPORT.OUT_DIR            := $$(if $$($1.OUT_DIR),$$($1.OUT_DIR),$$($1.NAME))
  $1.EXPORT.COMPONENT_FILES    := $$($1.SOURCE_FILES)

ifneq (,$$($1.NAME))
  $1.EXPORT.CONFIG_FILE   := $$(EXPORT_DIR)/$$($1.NAME)/$$(EXPORT_FILE_SHORT_NAME)
  $1.COMPILE_PREFIX       := export.compile.$$($1.NAME)
  $1.LINK_PREFIX          := export.link.$$($1.NAME)
  $1.RUN_PREFIX           := export.run.$$($1.NAME)
  DIST_DIRS               := $$(DIST_DIRS) $$(dir $$($1.EXPORT.CONFIG_FILE))  

  export: EXPORTCFG.$1
  
  .PHONY: EXPORTCFG.$1
  
  EXPORTCFG.$1: $$($1.EXPORT.CONFIG_FILE)    
  
  $$($1.EXPORT.CONFIG_FILE): $$(dir $$($1.EXPORT.CONFIG_FILE))
		@echo Create SDK export file for $$($1.NAME)...
		@echo '#Exports for $$($1.NAME)'> $$@
		@echo '$$($1.COMPILE_PREFIX).INCLUDE_DIRS := $$(notdir $$(EXPORT_INCLUDE_DIR))' >> $$@		
		@echo '$$($1.LINK_PREFIX).LIB_DIRS        := $$(notdir $$(EXPORT_LIB_DIR))' >> $$@
		@echo '$$($1.LINK_PREFIX).LIBS            := $$(strip $$($1.LIBS))' >> $$@		
		@echo '$$($1.LINK_PREFIX).LINK_INCLUDES   := $$($1.LINK_INCLUDES)' >> $$@
		@echo '$$($1.RUN_PREFIX).DLLS             := $$($1.DLLS)' >> $$@
		@echo '$$($1.RUN_PREFIX).DLL_DIRS         := $$(notdir $$(EXPORT_DLL_DIR))' >> $$@

endif

endef

#�������������� ���������� (������� ���������, ������� ��������, ������������� ���� � ������������� ����������)
define import_variables
#  $$(warning src='$1' dst='$2' path='$3')  

  $2.TYPE                 := $$(if $$($2.TYPE),$$($2.TYPE),$$($1.TYPE))
  $2.INCLUDE_DIRS         := $$($2.INCLUDE_DIRS) $$($1.INCLUDE_DIRS:%=$3%)
  $2.INCLUDE_FILES        := $$($2.INCLUDE_FILES) $$($1.INCLUDE_FILES)
  $2.SOURCE_DIRS          := $$($2.SOURCE_DIRS) $$($1.SOURCE_DIRS:%=$3%)
  $2.LIB_DIRS             := $$($2.LIB_DIRS) $$($1.LIB_DIRS:%=$3%)
  $2.DLL_DIRS             := $$($2.DLL_DIRS) $$($1.DLL_DIRS:%=$3%)
  $2.DLLS                 := $$($2.DLLS) $$($1.DLLS)
  $2.LIBS                 := $$($2.LIBS) $$($1.LIBS)
  $2.CHMS                 := $$($2.CHMS) $$($1.CHMS)
  $2.EXCLUDE_DEFAULT_LIBS := $$($2.EXCLUDE_DEFAULT_LIBS) $$($1.EXCLUDE_DEFAULT_LIBS)
  $2.COMPILER_CFLAGS      := $$($2.COMPILER_CFLAGS) $$($1.COMPILER_CFLAGS)
  $2.COMPILER_DEFINES     := $$($2.COMPILER_DEFINES) $$($1.COMPILER_DEFINES)
  $2.LINK_INCLUDES        := $$(strip $$($2.LINK_INCLUDES)) $$(strip $$($1.LINK_INCLUDES))
  $2.LINK_FLAGS           := $$($2.LINK_FLAGS) $$($1.LINK_FLAGS)
  $2.COMPONENTS           := $$($2.COMPONENTS) $$($1.COMPONENTS)
  $2.LINK_TOOL            := $$(if $$($2.LINK_TOOL),$$($2.LINK_TOOL),$$($1.LINK_TOOL))
  $2.LIB_TOOL             := $$(if $$($2.LIB_TOOL),$$($2.LIB_TOOL),$$($1.LIB_TOOL))
  $2.COMPILE_TOOL         := $$(if $$($2.COMPILE_TOOL),$$($2.COMPILE_TOOL),$$($1.COMPILE_TOOL))
  $2.RUN_TOOL             := $$(if $$($2.RUN_TOOL),$$($2.RUN_TOOL),$$($1.RUN_TOOL))
endef

#��������������� ������ �������� - ���������� ������ ������� (��� �����������, ��� ����, ��� ���������� �� �������)
define prepare_to_import_settings
# �������� ������������ �������
ifneq (,$$(filter $1,$$($3)))
  ifneq (1,$$(strip $$($(EXPORT_VAR_PREFIX).$1.MULTI_IMPORTS)))
    $3 := $$(foreach imp,$$($3),$$(if $$(filter $1,$$(imp)),,$$(imp)))
  endif
endif

  $3 := $$($3) $1

#�������� ������� ����������
ifeq (,$$(paths.$1))
  ifeq (,$$(strip $$(foreach profile,$$(PROFILES),$$(paths.$1.$$(profile)))))
    $$(error Component '$1' not exported (unresolved import))
  endif
endif

#�������������� ��������� ������������
  DEPENDENCY_IMPORTS := $$($(EXPORT_VAR_PREFIX).$1.IMPORTS) $$(foreach profile,$(PROFILES),$$($(EXPORT_VAR_PREFIX).$1.$$(profile).IMPORTS))

  $$(foreach imp,$$(DEPENDENCY_IMPORTS),$$(eval $$(call prepare_to_import_settings,$$(imp),$2,$3)))
endef

#�������������� �������� (��� �����������, ��� ����)
define import_settings
#��������� ��������  
  $$(eval $$(call import_variables,$(EXPORT_VAR_PREFIX).$1,$2,$$(patsubst $(COMPONENT_DIR)%,%,$$(paths.$1))))
  $$(foreach profile,$(PROFILES),$$(eval $$(call import_variables,$(EXPORT_VAR_PREFIX).$1.$$(profile),$2,$$(patsubst $(COMPONENT_DIR)%,%,$$(paths.$1)))))
endef

#������ �������� toolset-�������� (��� ����, ��� �������)
define import_toolset_settings
$$(foreach var,$$(filter $1.$2.%,$$(.VARIABLES)),$$(eval $$(var:$1.$2.%=$1.%) = $$($$(var:$1.$2.%=$1.%)) $$($$(var))))
endef

#��������� ������ ���� (��� ����)
define process_target_common
  PROCESSED_IMPORTS :=

    #���������� toolset-�������� � ������ ������ ��������
  $$(foreach profile,$$(PROFILES),$$(eval $1.IMPORTS := $$($1.IMPORTS) $$($1.$$(profile).IMPORTS)))  

    #������ ��������

  $1.PROCESSED_IMPORTS :=

#  $$(foreach imp,$$($1.IMPORTS),$$(eval $$(call import_settings,$$(imp),$1)))
  $$(foreach imp,$$($1.IMPORTS),$$(eval $$(call prepare_to_import_settings,$$(imp),$1,$1.PROCESSED_IMPORTS)))
  
  $$(foreach exclude_import,$$($1.EXCLUDE_IMPORTS),$$(eval $1.PROCESSED_IMPORTS := $$(subst $$(exclude_import),,$$($1.PROCESSED_IMPORTS))))

  $$(foreach imp,$$($1.PROCESSED_IMPORTS),$$(eval $$(call import_settings,$$(imp),$1)))

    #���������� toolset-�������� � ������ ������ ��������
  $$(foreach profile,$$(PROFILES),$$(eval $$(call import_toolset_settings,$1,$$(profile))))  

  DUMP.$1:
		@echo Dump target \'$1\' settings
		@$$(foreach var,$$(sort $$(filter $1.%,$(.VARIABLES) $1.PROCESSED_IMPORTS)),echo '    $$(var:$1.%=%) = $$($$(var))' && ) true

  dump: DUMP.$1

  .PHONY: DUMP.$1  

#��������� ������������� ������ ��� ������� ���� �����

  $$(eval $$(call process_target.$$(strip $$($1.TYPE)),$1))
  
#��������� �������� ������

  $1.EXPORT.COMPONENT_FILES := $$(call specialize_paths,$$($1.EXPORT.COMPONENT_FILES))  
  $1.EXPORT.OUT_DIR         := $$(if $$($1.EXPORT.OUT_DIR),$$(EXPORT_DIR)/$$($1.EXPORT.OUT_DIR),$$(EXPORT_DIR))

  $$(foreach source,$$($1.EXPORT.COMPONENT_FILES),$$(eval $$(call process_copy_files,$$(source),$$($1.EXPORT.OUT_DIR),$1)))
  
  $1.EXPORT.LIB_FILTER  := $$(if $$($1.EXPORT.LIB_FILTER),$$($1.EXPORT.LIB_FILTER),%)
  $1.EXPORT.LIBS        := $$(filter $$($1.EXPORT.LIB_FILTER),$$($1.EXPORT.LIBS))
  $1.EXPORT.LIBS        := $$(filter-out $$($1.EXPORT.LIB_EXCLUDE_FILTER),$$($1.EXPORT.LIBS))
  $1.EXPORT.LIBS        := $$($1.EXPORT.LIBS:%=$(LIB_PREFIX)%$(LIB_SUFFIX))
  $1.EXPORT.LIBS        := $$(foreach lib,$$($1.EXPORT.LIBS),$$(firstword $$(wildcard $$($1.EXPORT.LIB_DIRS:%=%/$$(lib))) $$(lib)))
  $1.EXPORT.INCLUDES    := $$(call specialize_paths,$$($1.EXPORT.INCLUDES))
  $1.EXPORT.DLLS        := $$($1.EXPORT.DLLS:%=$$($1.EXPORT.OUT_DIR)/$$(EXPORT_DLL_DIR)/$(DLL_PREFIX)%$(DLL_SUFFIX))
  $1.EXPORT.EXECUTABLES := $$($1.EXPORT.EXECUTABLES:%=$$(DIST_BIN_DIR)/%$(EXE_SUFFIX))
  $1.EXPORT.CHMS        := $$($1.EXPORT.CHMS:%=$$(DIST_INFO_DIR)/%.chm)

  export: $$($1.EXPORT.DLLS) $$($1.EXPORT.CHMS)

  $$(foreach source,$$($1.EXPORT.LIBS),$$(eval $$(call process_copy_files,$$(source),$$($1.EXPORT.OUT_DIR)/$$(EXPORT_LIB_DIR),$1)))
  $$(foreach source,$$($1.EXPORT.INCLUDES),$$(eval $$(call process_copy_files,$$(source),$$($1.EXPORT.OUT_DIR)/$$(EXPORT_INCLUDE_DIR),$1)))
  $$(foreach source,$$($1.EXPORT.EXECUTABLES),$$(eval $$(call process_copy_files,$$(source),$$($1.EXPORT.OUT_DIR)/$$(EXPORT_BIN_DIR),$1)))
  $$(foreach source,$$($1.EXPORT.CHMS),$$(eval $$(call process_copy_files,$$(source),$$($1.EXPORT.OUT_DIR)/$$(EXPORT_INFO_DIR),$1)))

  $$(foreach file,$$($1.EXPORT.DLLS),$$(eval $$(call create_extern_file_dependency,$$(file),$$($1.DLL_DIRS))))
endef

#�������� ������������ ���� ���� (��� ����)
define test_target_type
  ifeq (,$$(findstring $$(strip $$($1.TYPE)),$(VALID_TARGET_TYPES)))
    $$(error Wrong target type '$$(strip $$($1.TYPE))' at build target '$1' component-dir='$(COMPONENT_DIR)')
  endif
endef

###################################################################################################
#������� ������
###################################################################################################
all: build check
run: build
build: create-dirs
rebuild: clean build
reinstall: uninstall install
install: build
test: install
check: install
export: build
force:

.PHONY: build rebuild clean fullyclean run test check help create-dirs force dump info install uninstall reinstall export tar-dist

#������������� ������ ����� (� ����������� �� �������)
$(foreach profile,$(PROFILES),$(eval TARGETS := $$(TARGETS) $$(TARGETS.$$(profile))))  

#��������� ����� ����������
$(foreach target,$(filter $(targets),$(TARGETS)),$(eval $(call test_target_type,$(target))))
$(foreach target,$(filter $(targets),$(TARGETS)),$(eval $(call process_target_common,$(target))))

#�������� ���������
create-dirs: $(DIRS)

$(sort $(DIRS)):
	@mkdir -p $@

#�������
clean:
	@$(if $(wildcard $(ROOT_TMP_DIR)),cd $(ROOT_TMP_DIR) && $(RM) -r $(TMP_CLEAN_DIRS:$(ROOT_TMP_DIR)/%=%))

fullyclean: clean
	@$(RM) -r $(DIRS)

#�����������	
ifneq (,$($(INSTALL_TOOL)))

install: $(INSTALLATION_FLAG)

uninstall:
	@$(RM) -f $(INSTALLATION_FLAG)

#��������� ����� � ������ ������������ ����� ������� (������ ������������� �����)
define get_absolute_paths
export ROOT_ABS_PATH=`cd $(ROOT) && pwd`/ && for file in $1; do export ABS_PATH=`cd \`dirname $$file\`; pwd`/`basename $$file` && echo $${ABS_PATH/#$$ROOT_ABS_PATH/}; done
endef

#����������� (������ ����������� ������, ������ ����� ������, ����-����)
define do_installation
echo Install $(words $(sort $1 $2)) files... && \
$(call build_installation_command,$(sort $1 $2)) && \
echo Update installation registry... && \
echo >> $@ && echo $(patsubst $(ROOT)/%,%,$2) >> $3
endef

#��������� ������ ����� ������ ��� ����������� (������ �������������� ������, ������ ������������������� ������)
define get_new_installation_files
$(strip $(foreach file,$1,$(if $(filter $(file),$2),,$(ROOT)/$(file))))
endef

INSTALLATION_FILES := $(sort $(INSTALLATION_FILES) $(wildcard $(DIST_BIN_DIR)/*))

$(INSTALLATION_FLAG): NEW_INSTALLATION_FILES = $(call get_new_installation_files,$(shell $(call get_absolute_paths,$(INSTALLATION_FILES))),$(if $(wildcard $(INSTALLATION_FLAG)),$(sort $(shell cat $(INSTALLATION_FLAG)))))

$(INSTALLATION_FLAG): $(INSTALLATION_FILES) $(INSTALLATION_FLAGS)
	@$(call do_installation,$(filter-out %.$(INSTALLATION_FLAG_SUFFIX),$?),$(NEW_INSTALLATION_FILES),$@)

endif

#�������� ������ � �������������
tar-dist: dist
	@echo Create $(basename $(DIST_DIR)).tar...
	@tar -cf $(basename $(DIST_DIR)).tar $(DIST_DIR)
