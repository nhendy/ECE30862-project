cmake_minimum_required(VERSION 3.12)
project(ECE30862_project)

set(CMAKE_CXX_STANDARD 14)

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