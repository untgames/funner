###################################################################################################
#����������� � ���������
###################################################################################################
TARGETS := SCRIPT.LUA.SOURCES SCRIPT.LUA.TESTS

#SCRIPT_LUA sources
SCRIPT.LUA.SOURCES.TYPE             := static-lib
SCRIPT.LUA.SOURCES.NAME             := funner.script.lua
SCRIPT.LUA.SOURCES.SOURCE_DIRS      := sources
#SCRIPT.LUA.SOURCES.COMPILER_DEFINES := __STRICT_ANSI__
SCRIPT.LUA.SOURCES.IMPORTS				  := compile.script.core compile.common 

#ifneq (,$(filter x86,$(PROFILES)))
#SCRIPT.LUA.SOURCES.IMPORTS += compile.extern.luajit
#else
SCRIPT.LUA.SOURCES.IMPORTS += compile.extern.lua
#endif

#SCRIPT_LUA tests
SCRIPT.LUA.TESTS.TYPE        := test-suite
SCRIPT.LUA.TESTS.SOURCE_DIRS := tests
SCRIPT.LUA.TESTS.IMPORTS     := compile.script.core link.script.lua compile.common
