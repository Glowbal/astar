file(GLOB_RECURSE AStar_ASTAR_SOURCES *.h *.hpp *.c *.cpp)


SOURCE_GROUP("astar" FILES ${AStar_ASTAR_SOURCES})

add_library(AStar_astar STATIC ${AStar_ASTAR_SOURCES})
set_target_properties(AStar_astar PROPERTIES FOLDER AStar)
