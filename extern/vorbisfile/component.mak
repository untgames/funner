###################################################################################################
#������ �����
###################################################################################################
TARGETS := VORBISFILE_STATIC

#���� �1 - VORBISFILE_STATIC
VORBISFILE_STATIC.TYPE                  := static-lib
VORBISFILE_STATIC.NAME                  := extern.vorbisfile_static
VORBISFILE_STATIC.INCLUDE_DIRS          := include ../vorbis/include ../ogg/include
VORBISFILE_STATIC.SOURCE_DIRS           := sources
VORBISFILE_STATIC.LIB_DIRS              :=
VORBISFILE_STATIC.LIBS                  :=
VORBISFILE_STATIC.COMPILER_DEFINES      :=
VORBISFILE_STATIC.msvc.COMPILER_CFLAGS  := -wd4244
VORBISFILE_STATIC.g++.COMPILER_CFLAGS   := -Wno-unused
