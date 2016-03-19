
FILE(GLOB unified_headers
    "*.hpp"
    "*.h")

FILE(GLOB unified_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

LIST(SORT unified_headers)
LIST(SORT unified_sources)

SOURCE_GROUP(api\\unified\\Headers FILES ${unified_headers})
SOURCE_GROUP(api\\unified\\Sources FILES ${unified_sources})

FILE(GLOB cpp_sources
    "../cpp/*.cpp")

LIST(SORT cpp_sources)

SOURCE_GROUP(api\\cpp\\Sources FILES ${cpp_sources})

FILE(GLOB common_sources
  "../c/version.cpp"
  "../c/err_common.cpp"
  "../c/type_util.cpp"
  "../../backend/dim4.cpp"
  "../../backend/util.cpp"
  )

LIST(SORT common_sources)

SOURCE_GROUP(common FILES ${common_sources})

IF(NOT UNIX)
    ADD_DEFINITIONS(-DAFDLL)
ENDIF()

# OS Definitions
IF(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -pthread -Wno-comment")
ENDIF()

ADD_LIBRARY(af
            ${unified_headers}
            ${unified_sources}
            ${common_sources}
            ${cpp_sources}
            )

IF(${BUILD_CPU})
    ADD_DEPENDENCIES(af afcpu)
ENDIF()

IF(${BUILD_CUDA})
    ADD_DEPENDENCIES(af afcuda)
ENDIF()

IF(${BUILD_OPENCL})
    ADD_DEPENDENCIES(af afopencl)
ENDIF()

TARGET_LINK_LIBRARIES(af ${CMAKE_DL_LIBS})

SET_TARGET_PROPERTIES(af PROPERTIES
                      VERSION "${AF_VERSION}"
                      SOVERSION "${AF_VERSION_MAJOR}")

IF(APPLE)
    INSTALL(SCRIPT "${ArrayFire_SOURCE_DIR}/CMakeModules/osx_install/InstallTool.cmake")
ENDIF(APPLE)

####
# Installation (https://github.com/forexample/package-example)

install(
    TARGETS af
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)
