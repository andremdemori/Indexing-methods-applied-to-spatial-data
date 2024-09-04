#!/bin/bash

max=30

for i in `seq 1 $max`
do
   /home/demori/teste/arboretumR2/sample/sample-01_slimtree_2/Stars >>/home/demori/teste/arboretumR2/sample/sample-01_slimtree_2/logs/rodada_{$i}_Slim-tree.txt
done


