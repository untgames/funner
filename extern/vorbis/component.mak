###################################################################################################
#������ �����
###################################################################################################
TARGETS := VORBIS_STATIC

#���� �1 - VORBIS_STATIC
VORBIS_STATIC.TYPE                 := static-lib
VORBIS_STATIC.NAME                 := extern.vorbis_static
VORBIS_STATIC.INCLUDE_DIRS         := include ../ogg/include
VORBIS_STATIC.SOURCE_DIRS          := sources
VORBIS_STATIC.LIB_DIRS             :=
VORBIS_STATIC.LIBS                 :=
VORBIS_STATIC.COMPILER_DEFINES     :=
VORBIS_STATIC.msvc.COMPILER_CFLAGS := -wd4244 -wd4305
VORBIS_STATIC.g++.COMPILER_CFLAGS  := -Wno-unused -Wno-uninitialized
