# README #

This repository contains various **C** optimized version of the **Stochastic Gradient Descent x SoftSVM x Polynomial Kernel Method** algorithm.  
Provided optimizations make use of advanced programming concept such us **SIMD** parallelism, which is exploited by using **Intel SSE and AVX** instruction sets, and **Cache Blocking**.     
Implementations were subidived in two groups:
* 32 bit: single precision floating point data and Intel SSE instruction set.   
* 64 bit: double precision floating point data and Intel AVX instruction set.   


## Project Structure ##

### bash/ ###
Here-in Bash scripts for compiling and running each version of the algorithm can be found.  

### data/ ###
Here-in some dataset has been provided.   

### pyutils/ ###
Here-in Python scripts for assessing algorithm's accuracy have been provided. Binary Classification accuracy is compared with SkLearns's SVC Classifier.   

### src/ ###
Here-in C and Assembly source code can be found. Note that Assembly code is located under src/algorithm/sse and src/algorithm/avx.  

## Implementations Provided ##
For both 32 bit and 64 bit, the following implementations has been provided:
* C standard **SoftSvmPoly\[32|64\].c**;
* SIMD optimization **SoftSvmPolySimd\[32|64\].c**;
* SIMD + Cache-Blocking **SoftSvmPolyBlockWise\[32|64\].c**;
* SIMD + OpenMP **SoftSvmPolySimdOmp\[32|64\].c**.   

## Performance Considerations ##

Tests were done on an **Intel (R) i7 9750H CPU**.   
A 1000-dimensional dataset of 951 sample has been used for benchmarking.   
Algorithm is run for 1902 iterations.  

### 32-Bit ###
* **SoftSvmPoly32.c** requires **4.000 s** for completing. (96% Accuracy).   
* **SoftSvmPolySimd32.c** requires **0.506 s** for completing. **8x faster than SoftSvmPoly32.c** (96% Accuracy).   
* **SoftSvmPolyBlockWise32.c** requires **0.201 s** for completing. **20x faster than SoftSvmPoly32.c** (96% Accuracy).   


### 64-Bit ###
* **SoftSvmPoly64.c** requires **4.483 s** for completing. (97% Accuracy).  
* **SoftSvmPolySimd64.c** requires **0.725 s** for completing. **6x faster than SoftSvmPoly64.c** (97% Accuracy).   
* **SoftSvmPolyBlockWise64.c** requires **0.327 s** for completing. **13x faster than SoftSvmPoly64.c** (97% Accuracy).   