#!/bin/bash
for filename in $(find . | egrep '\.cpp$');
do 
  gcov -o . $filename; 
done
