cmake_minimum_required(VERSION 3.12)
project(ECE30862_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
#set(CMAKE_BINARY_DIR "./bin")
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/src/)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/cmake-build-release")


find_package(Boost 1.67.0 COMPONENTS system filesystem REQUIRED)



include_directories(inc)
include_directories(lib)
include_directories(lib/pugixml-1.9)
include_directories(lib/pugixml-1.9/contrib)
include_directories(lib/pugixml-1.9/src)
include_directories(lib/rapidxml-1.13)
include_directories(src)

add_executable(ECE30862_project
        inc/ConditionModel.h
        inc/Container.h
        inc/Creature.h
        inc/GameObjectModel.h
        inc/GameWorld.h
        inc/HasCondition.h
        inc/Item.h
        inc/Room.h
        inc/StatusCondition.h
        inc/Trigger.h
        lib/pugixml-1.9/contrib/foreach.hpp
        lib/pugixml-1.9/src/pugiconfig.hpp
        lib/pugixml-1.9/src/pugixml.cpp
        lib/pugixml-1.9/src/pugixml.hpp
        lib/rapidxml-1.13/rapidxml.hpp
        lib/rapidxml-1.13/rapidxml_iterators.hpp
        lib/rapidxml-1.13/rapidxml_print.hpp
        lib/rapidxml-1.13/rapidxml_utils.hpp
        src/GameWorld.cpp
        src/main.cpp
        src/sample.txt.xml
        CMakeLists.txt)




if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()


if(Boost_FOUND)

    target_link_libraries(ECE30862_project ${Boost_LIBRARIES})

endif()


#ACK
##https://stackoverflow.com/questions/28761323/how-to-include-external-library-boost-into-clion-c-project-with-cmake