#!/bin/bash


for filename in *.png; do
    ls $filename
    ./../build/im2stl $filename filename_extract_id
done
