include_directories(${PROJECT_SOURCE_DIR}/sys/include)
aux_source_directory(src MYSOURCEFILE)
add_library(MygraphicLib ${MYSOURCEFILE} include/GraphicList.h)
#target_include_directories(MygraphicLib PUBLIC sysLib)