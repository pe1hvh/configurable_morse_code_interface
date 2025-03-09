#!/bin/bash

projectName="configurable_morse_code_interface"
projectDirSource="../" 
projectDirTarget="../arduino_ide/$projectName" 

# Copy all .cpp (other than main.cpp) and .h files
cp $projectDirSource/lib/**/src/* $projectDirTarget

# Rename .cpp to .ino
for file in $projectDirTarget/*.cpp; do
    mv -- "$file" "${file%.cpp}.ino"
done


# Copy main.cpp to projectname.ino and rename #include main.h 
cp $projectDirSource/src/main.cpp $projectDirTarget/$projectName.ino
cp $projectDirSource/include/main.h $projectDirTarget/$projectName.h
sed -i 's/#include "main.h"/#include "configurable_morse_code_interface.h"/' "$projectDirTarget/$projectName.ino"