cmake_minimum_required(VERSION 3.10)
project(Algorithms_Ntua)

set(CMAKE_CXX_STANDARD 14)


add_executable(Poleodomia Programmatistikes/ask1/Poleodomia/poleodomia.cpp)
add_executable(Poleodomia_Faster Programmatistikes/ask1/Poleodomia/poleodomia_faster.cpp)

add_executable(Particles_v1 Programmatistikes/ask1/Particles/particles_v1.cpp)

add_executable(Drouk Programmatistikes/ask1/Particles/droukalis.cpp)

add_executable(Creosote Programmatistikes/ask2/Creosote/creosote.cpp)
add_executable(Creosote_v2 Programmatistikes/ask2/Creosote/creosote_v2.cpp)
add_executable(markella Programmatistikes/ask2/Creosote/algos2ex1.cpp)

add_executable(Credits Programmatistikes/ask2/Credits/credits.cpp)

file(GLOB SOURCES
        *.h
        *.cpp
        )

