#!/bin/bash

while IFS=" " read -r BC FC
do
 echo "*** Base ($BC) Final ($FC)"

CF=${FC,,}
 
 echo ${CF}.cpp

 sed "s/FINALCLASS/${FC}/; s/BASECLASS/${BC}/" template.h > ${CF}.h
 sed "s/FINALCLASS/${FC}/g; s/BASECLASS/${BC}/ ; s/INCLUDEH/${CF}.h/" template.cpp > ${CF}.cpp

done < "classes.txt"
