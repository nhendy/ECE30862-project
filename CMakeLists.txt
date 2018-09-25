cmake_minimum_required(VERSION 3.12)
project(ECE30862_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
#set(CMAKE_BINARY_DIR "./bin")
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin/)
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
        inc/ConditionFactory.hpp
        inc/Container.hpp
        inc/Creature.hpp
        inc/GameObjectModel.hpp
        inc/GameWorld.hpp
        inc/HasCondition.hpp
        inc/Item.hpp
        inc/Room.hpp
        inc/StatusCondition.hpp
        inc/Trigger.hpp
        lib/rapidxml-1.13/rapidxml.hpp
        lib/rapidxml-1.13/rapidxml_iterators.hpp
        lib/rapidxml-1.13/rapidxml_print.hpp
        lib/rapidxml-1.13/rapidxml_utils.hpp
        src/GameWorld.cpp
        src/main.cpp
        bin/sample.txt.xml
        CMakeLists.txt src/Room.cpp src/Trigger.cpp src/GameObjectModel.cpp inc/Condition.hpp src/Item.cpp src/ConditionFactory.cpp src/HasCondition.cpp src/StatusCondition.cpp)




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