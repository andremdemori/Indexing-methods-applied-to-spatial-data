#!/bin/bash

max=30

for i in `seq 1 $max`
do
   java -cp treeCompare.jar treeCompare.Main ../../../data/Total0000008col.txt ../../../data/points.csv ../../../data/distances.csv erro >> rodada_{$i}_Phtree.txt
done


