###################################################################################################
#������ ��� g++
###################################################################################################

###################################################################################################
#���������
###################################################################################################
LIB_SUFFIX   ?= a
OBJ_SUFFIX   ?= o
EXE_SUFFIX   ?= exe
DLL_SUFFIX   ?= dll
LIB_PREFIX   ?= lib
COMPILER_GCC ?= gcc
LINKER_GCC   ?= g++
LIB_GCC      ?= ar
PROFILES     += g++

###################################################################################################
#���������� ���������� (������ ����������, ������ ������������ ���������, ������� � ���������� �������,
#������ ��������, ����� ����������, pch ����)
###################################################################################################
define tools.g++.c++compile
$(call for_each_file,src,$1,echo $$src && $(COMPILER_GCC) $(COMMON_CFLAGS) -c -Wall -O7 -o "$3/$$(basename $$src $${src##*.})o" $(patsubst %,-I "%",$2) $5 $(patsubst %,-D %,$4) $$src)
endef

###################################################################################################
#�������� shared-library (��� ��������� �����)
###################################################################################################
define tools.link.dll
-shared -Wl,--out-implib,$(dir $1)$(LIB_PREFIX)$(notdir $(basename $1)).$(LIB_SUFFIX)
endef

###################################################################################################
#�������� ������ (��� ��������� �����, ������ ������, ������ ��������� �� ������������ ������������,
#������ ������������ �������� ��������, ����� ��������)
###################################################################################################
define tools.g++.link
$(LINKER_GCC) -o "$1" $(if $(filter %.$(DLL_SUFFIX),$1),$(call tools.link.dll,$1)) $(filter-out lib%.a,$2) $(patsubst %,-L "%",$3) $5 $(patsubst lib%.a,-l %,$(filter lib%.a,$2) $(COMMON_LINK_FLAGS) $(patsubst %,-u _%,$4))
endef

###################################################################################################
#������ ���������� (��� ��������� �����, ������ ������)
###################################################################################################
define tools.g++.lib
$(LIB_GCC) rcus $1 $2
endef

define tools.c++compile
$(call tools.g++.c++compile,$1,$2,$3,$4,$5,$6,$7,$8,$9)
endef

define tools.link
$(call tools.g++.link,$1,$2,$3,$4,$5,$6,$7,$8,$9)
endef

define tools.lib
$(call tools.g++.lib,$1,$2,$3,$4,$5,$6,$7,$8,$9)
endef

