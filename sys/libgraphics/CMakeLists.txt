SET(LIB_SRC
        exceptio.c
        genlib.c
        graphics.c
        random.c
        simpio.c
        strlib.c
        )
aux_source_directory(. DIR_SRCS)
message(${DIR_SRCS})
add_library(sysLib ${DIR_SRCS})

