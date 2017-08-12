# All the source files for the bot.
file(GLOB BOT_SOURCES "*.cpp" "*.h")

include_directories("${SC2Api_INCLUDE_DIRS}")

if (APPLE)
    # Supress annoying 'deprecated' warnings caused by sc2api headers.
    set(CMAKE_CXX_FLAGS "-Wno-deprecated")
endif ()

# Create the executable.
add_executable(CommandCenter ${BOT_SOURCES})
target_link_libraries(CommandCenter ${SC2Api_LIBRARIES})

if (APPLE)
    target_link_libraries(CommandCenter "-framework Carbon")
endif ()
