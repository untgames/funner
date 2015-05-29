###################################################################################################
#����������� � ���������
###################################################################################################
TARGETS += SDKS.FUNNER.CPP
TARGETS += SDKS.FUNNER.CPP.BUILD
                                       
SDKS.FUNNER.CPP.TYPE                       := sdk
SDKS.FUNNER.CPP.NAME                       := funner
SDKS.FUNNER.CPP.LIB_EXCLUDE_FILTER         := gdi32 ole32 uuid user32 shell32 wsock32 ws2_32 wldap32 openal32 wtsapi32 advapi32 crypt32 WbemUuid
SDKS.FUNNER.CPP.macosx.LIB_EXCLUDE_FILTER  := funner.extern.devil funner.extern.ilu pthread ldap ssl crypto
SDKS.FUNNER.CPP.android.LIB_EXCLUDE_FILTER := EGL GLESv1_CM funner.extern.openal32 dl log
SDKS.FUNNER.CPP.LIBS                       :=
SDKS.FUNNER.CPP.DLLS                       :=
SDKS.FUNNER.CPP.EXECUTABLES                := collada-converter
SDKS.FUNNER.CPP.IMPORTS                    += compile.system
SDKS.FUNNER.CPP.IMPORTS                    += compile.render.low_level
SDKS.FUNNER.CPP.IMPORTS                    += compile.media.geometry
SDKS.FUNNER.CPP.IMPORTS                    += compile.media.rfx
SDKS.FUNNER.CPP.IMPORTS                    += compile.media.animation
SDKS.FUNNER.CPP.IMPORTS                    += compile.media.image
SDKS.FUNNER.CPP.IMPORTS                    += compile.media.video
SDKS.FUNNER.CPP.IMPORTS                    += compile.media.font
SDKS.FUNNER.CPP.IMPORTS                    += compile.physics.manager
SDKS.FUNNER.CPP.IMPORTS                    += compile.scene_graph.core
SDKS.FUNNER.CPP.IMPORTS                    += compile.input.low_level
SDKS.FUNNER.CPP.IMPORTS                    += compile.input.manager
SDKS.FUNNER.CPP.IMPORTS                    += compile.input.window_driver
SDKS.FUNNER.CPP.IMPORTS                    += compile.math.curves
SDKS.FUNNER.CPP.IMPORTS                    += compile.sound.scene_player
SDKS.FUNNER.CPP.IMPORTS                    += compile.script.core
SDKS.FUNNER.CPP.IMPORTS                    += compile.network
SDKS.FUNNER.CPP.IMPORTS                    += compile.render.debug_render
SDKS.FUNNER.CPP.IMPORTS                    += compile.math.bound_volumes
SDKS.FUNNER.CPP.IMPORTS                    += link.common
SDKS.FUNNER.CPP.IMPORTS                    += link.system
SDKS.FUNNER.CPP.IMPORTS                    += link.render.low_level.opengl_driver
SDKS.FUNNER.CPP.IMPORTS                    += link.media.geometry.xmesh
SDKS.FUNNER.CPP.IMPORTS                    += link.media.geometry.binmesh
SDKS.FUNNER.CPP.IMPORTS                    += link.media.geometry
SDKS.FUNNER.CPP.IMPORTS                    += link.media.rfx
#SDKS.FUNNER.CPP.IMPORTS                    += link.media.rfx.default_serializers
SDKS.FUNNER.CPP.IMPORTS                    += link.media.animation.xanim
SDKS.FUNNER.CPP.IMPORTS                    += link.media.animation.binanim
SDKS.FUNNER.CPP.IMPORTS                    += link.media.image
SDKS.FUNNER.CPP.IMPORTS                    += link.media.image.dds
SDKS.FUNNER.CPP.IMPORTS                    += link.media.sound.default_decoders
SDKS.FUNNER.CPP.IMPORTS                    += link.media.sound.snddecl
SDKS.FUNNER.CPP.IMPORTS                    += link.media.video.theora
SDKS.FUNNER.CPP.IMPORTS                    += link.media.font.xfont
SDKS.FUNNER.CPP.IMPORTS                    += link.media.physics.xphys
SDKS.FUNNER.CPP.IMPORTS                    += link.scene_graph.core
SDKS.FUNNER.CPP.IMPORTS                    += link.sound.scene_player
SDKS.FUNNER.CPP.IMPORTS                    += link.sound.low_level.openal_driver
SDKS.FUNNER.CPP.IMPORTS                    += link.physics.low_level.bullet_driver
SDKS.FUNNER.CPP.IMPORTS                    += link.physics.manager
SDKS.FUNNER.CPP.IMPORTS                    += link.input.manager
SDKS.FUNNER.CPP.IMPORTS                    += link.input.window_driver
SDKS.FUNNER.CPP.IMPORTS                    += link.input.manager.xkeymap
SDKS.FUNNER.CPP.IMPORTS                    += link.input.manager.xkeyreg
SDKS.FUNNER.CPP.IMPORTS                    += link.script.lua
SDKS.FUNNER.CPP.IMPORTS                    += link.engine.script_binds.sg
SDKS.FUNNER.CPP.IMPORTS                    += link.engine.script_binds.lua_override
SDKS.FUNNER.CPP.IMPORTS                    += link.engine.script_binds.math
SDKS.FUNNER.CPP.IMPORTS                    += link.engine.script_binds.common
SDKS.FUNNER.CPP.IMPORTS                    += link.engine.launcher
SDKS.FUNNER.CPP.IMPORTS                    += link.network
SDKS.FUNNER.CPP.IMPORTS                    += link.render.debug_render
SDKS.FUNNER.CPP.IMPORTS                    += link.math.bound_volumes
SDKS.FUNNER.CPP.IMPORTS                    += run.extern.devil
SDKS.FUNNER.CPP.IMPORTS                    += run.extern.zzip
SDKS.FUNNER.CPP.IMPORTS                    += run.sound.low_level.openal_driver
#SDKS.FUNNER.CPP.IMPORTS                    += info.math.bound_volumes
#SDKS.FUNNER.CPP.IMPORTS                    += info.common
#SDKS.FUNNER.CPP.IMPORTS                    += info.input.low_level
#SDKS.FUNNER.CPP.IMPORTS                    += info.input.manager
#SDKS.FUNNER.CPP.IMPORTS                    += info.math.vecmath
#SDKS.FUNNER.CPP.IMPORTS                    += info.math.curves
#SDKS.FUNNER.CPP.IMPORTS                    += info.media.image
#SDKS.FUNNER.CPP.IMPORTS                    += info.media.animation
#SDKS.FUNNER.CPP.IMPORTS                    += info.media.geometry
#SDKS.FUNNER.CPP.IMPORTS                    += info.media.sound
#SDKS.FUNNER.CPP.IMPORTS                    += info.media.video
#SDKS.FUNNER.CPP.IMPORTS                    += info.media.rfx
#SDKS.FUNNER.CPP.IMPORTS                    += info.physics.low_level
#SDKS.FUNNER.CPP.IMPORTS                    += info.render.low_level
#SDKS.FUNNER.CPP.IMPORTS                    += info.scene_graph.core
#SDKS.FUNNER.CPP.IMPORTS                    += info.system info.xtl
#SDKS.FUNNER.CPP.IMPORTS                    += info.script.core
SDKS.FUNNER.CPP.win32.IMPORTS              := link.input.direct_input_driver
SDKS.FUNNER.CPP.EXCLUDE_IMPORTS            := link.common.auto_license_generator                                             

SDKS.FUNNER.CPP.BUILD.TYPE           := sdk
SDKS.FUNNER.CPP.BUILD.OUT_DIR        := funner/build
SDKS.FUNNER.CPP.BUILD.SOURCE_FILES   := ../../../build
