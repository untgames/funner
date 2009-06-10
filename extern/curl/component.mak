TARGETS := EXTERN.CURL.SOURCES EXTERN.CURL.TESTS

EXTERN.CURL.SOURCES.TYPE                   := static-lib
EXTERN.CURL.SOURCES.NAME                   := funner.extern.curl
EXTERN.CURL.SOURCES.INCLUDE_DIRS           := include
EXTERN.CURL.SOURCES.SOURCE_DIRS            := sources
EXTERN.CURL.SOURCES.COMPILER_DEFINES       := CURL_STATICLIB BUILDING_LIBCURL
EXTERN.CURL.SOURCES.macosx.COMPILER_CFLAGS := -Wno-uninitialized

EXTERN.CURL.TESTS.TYPE                 := test-suite
EXTERN.CURL.TESTS.SOURCE_DIRS          := tests
EXTERN.CURL.TESTS.INCLUDE_DIRS         := sources
EXTERN.CURL.TESTS.INCLUDE_FILES        := first.c testutil.c
EXTERN.CURL.TESTS.IMPORTS              := compile.static.mak link.static.mak
EXTERN.CURL.TESTS.msvc.COMPILER_CFLAGS := -wd4700
EXTERN.CURL.TESTS.g++.COMPILER_CFLAGS  := --no-warn