cmake_minimum_required (VERSION 2.8.3)
project (PythonCxxEmbedding)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()

#python
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

SET(
	CXX_SRC
	${CMAKE_SOURCE_DIR}/codes/cxx/main.cxx
	)

SET(
	CXX_HDR
	)

SET(Python_SRC_DIR ${CMAKE_SOURCE_DIR}/codes/python)

FILE(GLOB Python_SRC ${Python_SRC_DIR}/*.py)

add_executable(PythonCxxEmbedding ${CXX_SRC} ${Python_SRC})
target_link_libraries(PythonCxxEmbedding ${PYTHON_LIBRARIES})

#Grouping in MSVC
SOURCE_GROUP("Headers" FILES ${CXX_HDR})
SOURCE_GROUP("Sources" FILES ${CXX_SRC})
SOURCE_GROUP("Python Sources" FILES ${Python_SRC})

#copy python files to build directory
macro(copy_python_files srcDir destDir)
    message(STATUS "Configuring python files")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            # message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(copy_python_files)

copy_python_files(${Python_SRC_DIR} ${CMAKE_BINARY_DIR}/Debug)
copy_python_files(${Python_SRC_DIR} ${CMAKE_BINARY_DIR}/RELEASE)