SET(LIB_SRC
        include/exception.h
        include/extgraph.h
        include/gcalloc.h
        include/genlib.h
        include/graphics.h
        include/random.h
        include/simpio.h
        include/strlib.h
        )
SET(DIR_SRCS
        libgraphics/exceptio.cpp
        libgraphics/genlib.cpp
        libgraphics/graphics.cpp
        libgraphics/random.cpp
        libgraphics/simpio.cpp
        libgraphics/strlib.cpp

        )
#aux_source_directory(libgraphics DIR_SRCS)
#message(${DIR_SRCS})
add_library(sysLib ${DIR_SRCS} ${LIB_SRC})

