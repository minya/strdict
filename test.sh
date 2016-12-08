#!/bin/bash

make clean
make

if [ -f "huge.txt" ];
then
   echo "File huge.txt already exists."
else
   echo "generating huge.txt..."
   python gen_huge_file.py
   echo "huge.txt done"
fi

echo "begin YES test:"
cat huge.txt | ./strdict huge.txt | uniq
echo "end YES test. You should have seen YES"

echo "begin NO test:"
cat huge.txt | sed -e 's/^/u/g' | ./strdict huge.txt | uniq
echo "end NO test. You should have seen NO"
