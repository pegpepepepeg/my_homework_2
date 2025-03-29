#!/bin/bash

echo -e './differentiator.o --eval "x*y" x=2 y=4\n Expecting answer: 8'
#./differentiator.o --eval "x*y" x=2 y=4
./differentiator.o --eval "x y *" x=2 y=4
#echo

echo -e './differentiator.o --eval "x*y" x=-1 y=0.5\n Expecting answer: -0.5'
#./differentiator.o --eval "x*y" x=-1 y=0.5
./differentiator.o --eval "x y *" x=-1 y=0.5
#echo

echo -e './differentiator.o --eval "x^y" x=2 y=5\n Expecting answer: 32'
#./differentiator.o --eval "x^y" x=2 y=5
./differentiator.o --eval "x y ^" x=2 y=5
#echo

echo -e './differentiator.o --eval "x^y^x" x=2 y=5\n Expecting answer: 3.3554432 × 10^7'
#./differentiator.o --eval "x^y^x" x=2 y=5
./differentiator.o --eval "x y x ^ ^" x=2 y=5
#echo

echo -e './differentiator.o --eval "(x^y)^x" x=2 y=5\n Expecting answer: 1024'
#./differentiator.o --eval "(x^y)^x" x=2 y=5
./differentiator.o --eval "x y ^ x ^" x=2 y=5
#echo

echo -e './differentiator.o --eval "x^(y^x)" x=2 y=5\n Expecting answer: 3.3554432 × 10^7'
#./differentiator.o --eval "x^(y^x)" x=2 y=5
./differentiator.o --eval "x y x ^ ^" x=2 y=5
#echo

echo -e './differentiator.o --eval "x/y" x=2 y=4\n Expecting answer: 1/2'
./differentiator.o --eval "x y /" x=2 y=4
#echo

echo -e './differentiator.o --eval "x/y" x=2 y=0\n Expecting answer: Error'
./differentiator.o --eval "x y /" x=2 y=0
#echo

echo -e './differentiator.o --eval "ln(x)" x=2\n Expecting answer 0.6931'
#./differentiator.o --eval "ln(x)" x=2
./differentiator.o --eval "x ln" x=2
#echo

echo -e './differentiator.o --eval "ln(x)" x=2.718281828\n Expecting answer: 1'
#./differentiator.o --eval "ln(x)" x=2.718281828
./differentiator.o --eval "x ln" x=2.718281828
#echo

echo -e './differentiator.o --eval "ln(x)" x=0\n Expecting answer: inf'
#./differentiator.o --eval "ln(x)" x=0
./differentiator.o --eval "x ln" x=0
#echo

echo -e './differentiator.o --eval "ln(x)" x=-1\n Expecting answer: i*pi'
#./differentiator.o --eval "ln(x)" x=-1
./differentiator.o --eval "x ln" x=-1
#echo

echo -e './differentiator.o --eval "x*y" x=1-i y=2+3i\n Expecting answer: 3 + 2i'
#./differentiator.o --eval "x*y" x=1-i y=2+3i
./differentiator.o --eval "x y *" x=1-1i y=2+3i
#echo

echo -e './differentiator.o --diff "x * sin(x)" --by x\n Expecting answer: sin(x) + x*cos(x)'
#./differentiator.o --diff "x * sin(x)" --by x
./differentiator.o --diff "x x sin *" --by x
#echo

echo -e './differentiator.o --diff "ln(x) / cos(x)" --by x\n Expecting answer: x * sin(x)'
#./differentiator.o --diff "ln(x) / cos(x)" --by x
./differentiator.o --diff "x ln x cos /" --by x
#echo

echo -e './differentiator.o --diff "x^y" --by x\n Expecting answer: y * x^(y-1)'
#./differentiator.o --diff "x^y" --by x
./differentiator.o --diff "x y ^" --by x
#echo

echo -e './differentiator.o --diff "x^y" --by y\n Expecting answer: x^y * log(x)'
./differentiator.o --diff "x y ^" --by y
#echo

echo -e './differentiator.o --diff "x^x" --by x\n Expecting answer: x^x * (log(x) + 1)'
./differentiator.o --diff "x x ^" --by x
#echo