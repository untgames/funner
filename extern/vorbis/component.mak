###################################################################################################
#������ �����
###################################################################################################
TARGETS := VORBIS_STATIC

#���� �1 - VORBIS_STATIC
VORBIS_STATIC.TYPE             := static-lib              #��� ����
VORBIS_STATIC.NAME             := vorbis_static           #��� ��������� �����
VORBIS_STATIC.INCLUDE_DIRS     := include ../ogg/include  #������������� ���� � ��������� c ������������� �������
VORBIS_STATIC.SOURCE_DIRS      := sources    						  #������������� ���� � ��������� c ��������� �������
VORBIS_STATIC.LIB_DIRS         :=                         #������������� ���� � ��������� � ������������
VORBIS_STATIC.LIBS             :=                         #������ ������������ ��� �������� ���������
VORBIS_STATIC.COMPILER_DEFINES :=  					              #����������� ������
VORBIS_STATIC.COMPILER_CFLAGS  :=                         #����� ������ (������� �� ������������)
