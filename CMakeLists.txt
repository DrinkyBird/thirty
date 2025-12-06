cmake_minimum_required(VERSION 3.10)
project(thirty LANGUAGES C VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)

find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(CURL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(readline REQUIRED IMPORTED_TARGET readline)

set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})
set(project_version ${CMAKE_PROJECT_VERSION})
configure_file(version.h.in ${GENERATED_DIR}/version.h)

add_executable(thirty
    src/blocks.c
    src/blocks.h
    src/buffer.c
    src/buffer.h
    src/client.c
    src/client.h
    src/commands.c
    src/commands.h
    src/config.c
    src/config.h
    src/cpe.c
    src/heartbeat.c
    src/log.c
    src/log.h
    src/cpe.h
    src/main.c
    src/map.c
    src/map.h
    src/mapgen.c
    src/mapgen_classic.c
    src/mapgen_debug.c
    src/mapgen_flat.c
    src/mapgen_seantest.c
    src/mapimage.c
    src/mapimage.h
    src/mapsave.c
    src/mapsend.c
    src/namelist.c
    src/namelist.h
    src/nbt.c
    src/nbt.h
    src/perlin.c
    src/perlin.h
    src/rng.c
    src/rng.h
    src/server.c
    src/server.h
    src/util.c
    src/util.h

    lib/b64.c
    lib/b64.h
    lib/md5.c
    lib/md5.h
    lib/sha1.c
    lib/sha1.h
    lib/stb_image_write.c
    lib/stb_image_write.h
)

add_custom_target(hginfo
        COMMAND hg identify --config-file "${CMAKE_SOURCE_DIR}/hginfo.tmpl" -T "{cheader}" -r . > ${GENERATED_DIR}/hginfo.h
        BYPRODUCTS ${GENERATED_DIR}/hginfo.h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Updating Mercurial revision info"
        VERBATIM
)
add_dependencies(thirty hginfo)

target_link_libraries(thirty PRIVATE Threads::Threads ZLIB::ZLIB CURL::libcurl PkgConfig::readline)
target_include_directories(thirty PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/lib ${GENERATED_DIR})

if (WIN32)
    target_link_libraries(thirty PRIVATE bcrypt ws2_32)
else ()
    target_link_libraries(thirty PRIVATE m)
endif ()