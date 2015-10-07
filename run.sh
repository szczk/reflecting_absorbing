#! /bin/bash


./main.x --noise 0.4 --storage 'results'
./main.x --noise 1.4 --storage 'results'
./main.x --noise 5.4 --storage 'results'
./main.x --noise 8.4 --storage 'results'
./main.x --noise 12.4 --storage 'results'

gnuplot *.plt
