#!/bin/sh

cd au_to_csv
cmake .
make 
cd ..

for type in au_files/*; do
    if [ -d "$type" ]; then
        echo "Prepare type $type"
        mkdir -p ./csv_files/$type/
        for file in "$type"/*.au; do
            echo "Prepare au file $file"
            mkdir -p ./csv_files/$type/
            ./au_to_csv/machine_learning.o "$file"
        done
    fi
done
