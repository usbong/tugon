#!/bin/bash

# Usbong Tugon System
#
# C/C++ Computer Language and Simple Directmedia Layer (SDL) + SDL Image
#
# Compile and Link Multiple Source Files
#
# @company: USBONG
# @author: SYSON, MICHAEL B.
# @date created: 20211111
# @last updated: 20211214
# @website address: http://www.usbong.ph
#
# Reference:
# 1) https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html;
# last accessed: 20211111

#note: sequence

g++ -c mainLinux.cpp
g++ -c MyDynamicObject.cpp
g++ -c Ipis.cpp
g++ -c Unit.cpp
g++ -c Sdlwav.cpp
g++ -c Font.cpp
g++ -c Text.cpp

g++ -pthread -o ./output/UsbongTugonLinux mainLinux.o MyDynamicObject.o Ipis.o Unit.o Sdlwav.o Font.o Text.o -lSDL2 -lSDL2_image -lSDL2_mixer
