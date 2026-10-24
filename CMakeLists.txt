cmake_minimum_required(VERSION 3.21)
project(EclipseQQQ)

find_package(Geode REQUIRED)

add_geode_mod(EclipseQQQ
    src/main.cpp
)

