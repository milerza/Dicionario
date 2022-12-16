#!/bin/bash
rm -r ./out/*
./analisamem/bin/analisamem -i arv.log -p ./out/
gnuplot ./out/*.gp