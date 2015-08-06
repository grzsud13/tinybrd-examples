#!/usr/bin/env bash

rm -f *.zip

mkdir tmp
mkdir tmp/tinyBrdExamples

zip -r tmp/TSM.zip tinyBrdTemp connectionTester tinyBrdLight
cd tmp/tinyBrdExamples
unzip ../TSM
cd ..
zip -r ../tinyBrdExamples.zip tinyBrdExamples
cd ..
rm -fR tmp

