###################################################################################################
#����������� � ���������
###################################################################################################
TARGETS := HSSERVER.SOURCES HSSERVER.TESTS

HSSERVER.SOURCES.TYPE         := static-lib
HSSERVER.SOURCES.NAME         := plarium.hsserver
HSSERVER.SOURCES.SOURCE_DIRS  += sources
HSSERVER.SOURCES.IMPORTS      := compile.plarium.hsserver compile.plarium.system

HSSERVER.TESTS.TYPE        := test-suite
HSSERVER.TESTS.SOURCE_DIRS := tests
HSSERVER.TESTS.IMPORTS     := compile.plarium.hsserver compile.plarium.system link.plarium.hsserver link.plarium.system
