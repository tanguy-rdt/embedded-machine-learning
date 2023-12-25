### debug

``` bash
cmake -DCMAKE_BUILD_TYPE=Debug .     
make
./machine_learning.o 
```

### default

``` bash
cmake .
make
./machine_learning.o 
```

### clean

``` bash
make clean
cmake -P CMakeClean.cmake  
```