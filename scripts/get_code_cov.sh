#!/bin/bash
for filename in $(find . | egrep "\.cpp" | egrep -v "main\.cpp" | egrep -v "qrc_.*\.cpp"); 
do
  echo $filename
  gcov -n -o . $filename; 
done
