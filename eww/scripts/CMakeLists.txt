cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(Ewwscripts)

# Enable pkg-config support
find_package(PkgConfig REQUIRED)

# Find required packages via pkg-config
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GIO REQUIRED gio-unix-2.0)
pkg_check_modules(LIBNM REQUIRED libnm)
pkg_check_modules(PULSEAUDIO REQUIRED libpulse)
pkg_check_modules(WAYLAND_CLIENT REQUIRED wayland-client)

# Create a common library for the PulseAudio volume fetching code.
# Assume you have volume_fetcher.h and volume_fetcher.c in your source directory.
add_library(volume_fetcher STATIC volume_fetcher.c)
target_include_directories(volume_fetcher PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PULSEAUDIO_INCLUDE_DIRS}
)
target_compile_options(volume_fetcher PRIVATE ${PULSEAUDIO_CFLAGS_OTHER})
target_link_libraries(volume_fetcher PRIVATE ${PULSEAUDIO_LIBRARIES})

# Create the executable
add_executable(eww_toggle eww_toggle.c)
add_executable(get_network get_network.c)
add_executable(get_battery get_battery.c)
add_executable(get_volume get_volume.c)
add_executable(get_network_icon get_network_icon.c)
add_executable(get_volume_icon get_volume_icon.c)
add_executable(get_battery_icon get_battery_icon.c)
add_executable(media_image media_image.c)

target_include_directories(eww_toggle PRIVATE ${WAYLAND_CLIENT_INCLUDE_DIRS})
target_link_libraries(eww_toggle PRIVATE ${WAYLAND_CLIENT_LIBRARIES})

# Include directories from pkg-config
target_include_directories(get_network PRIVATE
    ${GLIB_INCLUDE_DIRS}
    ${GIO_INCLUDE_DIRS}
    ${LIBNM_INCLUDE_DIRS}
)

# Add compile options if needed (e.g., additional flags provided by pkg-config)
target_compile_options(get_network PRIVATE
    ${GLIB_CFLAGS_OTHER}
    ${GIO_CFLAGS_OTHER}
    ${LIBNM_CFLAGS_OTHER}
)

# Link libraries
target_link_libraries(get_network
    ${GLIB_LIBRARIES}
    ${GIO_LIBRARIES}
    ${LIBNM_LIBRARIES}
)

# For the volume-related executables, link to our common volume_fetcher library.
target_link_libraries(get_volume PRIVATE
	volume_fetcher
)

target_include_directories(get_network_icon PRIVATE
    ${GLIB_INCLUDE_DIRS}
    ${GIO_INCLUDE_DIRS}
    ${LIBNM_INCLUDE_DIRS}
)

# Add compile options if needed (e.g., additional flags provided by pkg-config)
target_compile_options(get_network_icon PRIVATE
    ${GLIB_CFLAGS_OTHER}
    ${GIO_CFLAGS_OTHER}
    ${LIBNM_CFLAGS_OTHER}
)

# Link libraries
target_link_libraries(get_network_icon
    ${GLIB_LIBRARIES}
    ${GIO_LIBRARIES}
    ${LIBNM_LIBRARIES}
)

# Link libraries
target_link_libraries(get_volume_icon PRIVATE
	volume_fetcher
)

# Include directories from pkg-config
target_include_directories(media_image PRIVATE
    ${GLIB_INCLUDE_DIRS}
    ${GIO_INCLUDE_DIRS}
)

# Add compile options if needed (e.g., additional flags provided by pkg-config)
target_compile_options(media_image PRIVATE
    ${GLIB_CFLAGS_OTHER}
    ${GIO_CFLAGS_OTHER}
)

# Link libraries
target_link_libraries(media_image
    ${GLIB_LIBRARIES}
    ${GIO_LIBRARIES}
    curl
)
