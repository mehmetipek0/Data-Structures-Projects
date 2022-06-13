# Homework 4 Hashing

Write a single program in C. Create a struct array and put every information, that data.txt file consist, into that struct array. 

Array size depends on you however, use as minimum size as possible. Implement **5 different hash functions** (please be creative) and measure the performance of each hash function and output the report to the screen. If you are going to measure the effect of array size, please run 5 hash functions for every array size you tried.

Every step or instruction must be counted, especially the linear probing like collusion resolution parts. Don't use time as a measurement but use complexity analysis or instructions count as a performance measurement technique. Create your formula for the performance report. Include array size in performance measurement.

At the end of your report please show and indicate the most effective hash function and/or array size.

Please use my main.c file. Do not create a new c file. We only work with C files don't use C++ or CPP files.
Your outputs must be meaningful. Please use complete sentences.

Put a single screenshot of outputs and update this README with outputs also.

## Output:

TableSize is 273 for each array.
Collision resolution type is Linear Probing.

Number modding hash function:
There are 116 collisions

Name square modding hash function:
There are 144 collisions

Grade modding hash function:
There are 192 collisions

Name truncation hash function:
There are 206 collisions

Name folding hash function:
There are 175 collisions

TableSize is 273 for each array.
Collision resolution type is Quadratic Probing.

Number modding hash function:
There are 116 collisions

Name square modding hash function:
There are 141 collisions

Grade modding hash function:
There are 193 collisions

Name truncation hash function:
There are 203 collisions

Name folding hash function:
There are 162 collisions

When table size is 273, the best hash function is Key mod N
(number modding) hashing with numbers.
