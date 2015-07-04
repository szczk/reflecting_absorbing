#! /bin/bash


./main.x --noise 0.4
./main.x --noise 1.4
./main.x --noise 5.4
./main.x --noise 8.4
./main.x --noise 12.4

gnuplot *.plt
