cmake_minimum_required(VERSION 3.10)
project(LinEngine_Test)

FILE(GLOB source *.cpp *.h)

add_executable(LinEngine_Test ${source})