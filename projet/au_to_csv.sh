#!/bin/bash

cd au_to_csv
cmake .
make 
cd ..

for type in au_files/*; do
    if [ -d "$type" ]; then
        mkdir ./csv_files/$type/
        echo "\t Prepare type $type"
        for file in "$type"/*.au; do
            echo "\tPrepare au file $file"
            ./au_to_csv/machine_learning.o "$file"
        done
    fi
done
