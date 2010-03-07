# Link exports
export.link.render.low_level.opengl_driver.LIBS              := funner.render.low_level.opengl_driver
export.link.render.low_level.opengl_driver.LINK_INCLUDES     := OpenGLDriver
export.link.render.low_level.opengl_driver.IMPORTS           := link.render.low_level link.common.wxf
export.link.render.low_level.opengl_driver.win32.LIBS        := gdi32
export.link.render.low_level.opengl_driver.macosx.LINK_FLAGS := -framework IOKit -framework AGL
export.link.render.low_level.opengl_driver.iphone.LINK_FLAGS := -framework OpenGLES
export.link.render.low_level.opengl_driver.bada.LIBS         := FGraphicsEgl FGraphicsOpengl

#Run exports (don't remove - used for common imports at run target)
export.run.render.low_level.opengl_driver.IMPORTS :=

# Win32 egl flags
ifeq (,$(filter gles,$(PROFILES)))
export.link.render.low_level.opengl_driver.win32.IMPORTS := link.extern.gles_win32
export.run.render.low_level.opengl_driver.win32.IMPORTS  := run.extern.gles_win32
endif
