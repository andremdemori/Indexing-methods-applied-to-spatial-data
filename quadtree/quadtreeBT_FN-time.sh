#!/bin/bash

max=30

QUADTREE_CODE=./QuadtreeTime/application.py

DATA=./Total000000.csv

LOG_QUADTREE_CODE=./logs_objetos/QuadtreeTime_Total000000_executio


for i in `seq 1 $max`
do
    python $QUADTREE_CODE  $DATA 1 0.0041666666666667 >> ./logs_objetos/QuadtreeTime_Total00000_round_${i}.txt
done
