# Compile exports
export.compile.media.particles.INCLUDE_DIRS := include
export.compile.media.particles.IMPORTS      := compile.math.vecmath compile.math.bound_volumes

# Link exports
export.link.media.particles.LIBS    := funner.media.particles
export.link.media.particles.IMPORTS := link.common
