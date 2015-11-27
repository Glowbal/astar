file(GLOB_RECURSE AStar_CLI_SOURCES *.h *.hpp *.c *.cpp)

include_directories ("${PROJECT_SOURCE_DIR}")

add_executable(AStar_cli ${AStar_CLI_SOURCES})
target_link_libraries(AStar_cli AStar_astar)
add_dependencies(AStar_cli AStar_astar)
SET_TARGET_PROPERTIES(AStar_cli PROPERTIES PREFIX "")
set_target_properties(AStar_cli PROPERTIES FOLDER AStar)
