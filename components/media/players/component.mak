TARGETS        := MEDIA.PLAYERS.CORE MEDIA.PLAYERS.TESTS
TARGETS.iphone := MEDIA.PLAYERS.IPHONE MEDIA.PLAYERS.IPHONE.TESTS

#MediaPlayer core
MEDIA.PLAYERS.CORE.TYPE                 := static-lib
MEDIA.PLAYERS.CORE.NAME                 := funner.media.players.core
MEDIA.PLAYERS.CORE.SOURCE_DIRS          := sources/core
MEDIA.PLAYERS.CORE.IMPORTS              := compile.media.players compile.common
MEDIA.PLAYERS.CORE.msvc.COMPILER_CFLAGS := -wd4355

#MediaPlayers iPhone
MEDIA.PLAYERS.IPHONE.TYPE            := static-lib
MEDIA.PLAYERS.IPHONE.NAME            := funner.media.players.iphone
MEDIA.PLAYERS.IPHONE.SOURCE_DIRS     := sources/iphone
MEDIA.PLAYERS.IPHONE.IMPORTS         := compile.media.players compile.common
MEDIA.PLAYERS.IPHONE.COMPILER_CFLAGS := -I$(IPHONE_SDK_PATH)/System/Library/Frameworks/AVFoundation.framework/Headers/ \
                                        -I$(IPHONE_SDK_PATH)/System/Library/Frameworks/Foundation.framework/Headers/ \
                                        -I$(IPHONE_SDK_PATH)/System/Library/Frameworks/MediaPlayer.framework/Headers/

#MediaPlayer tests
MEDIA.PLAYERS.TESTS.TYPE        := test-suite
MEDIA.PLAYERS.TESTS.SOURCE_DIRS := tests/core
MEDIA.PLAYERS.TESTS.IMPORTS     := compile.media.players link.media.players.core compile.common

#MediaPlayer tests
MEDIA.PLAYERS.IPHONE.TESTS.TYPE        := test-suite
MEDIA.PLAYERS.IPHONE.TESTS.SOURCE_DIRS := tests/iphone
MEDIA.PLAYERS.IPHONE.TESTS.IMPORTS     := compile.media.players link.media.players.iphone
