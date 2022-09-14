#!/bin/bash
for i in 1 2 3 4 5 6 7 8 9 10; do
  
    perf stat -e L1-dcache-loads,L1-dcache-load-misses,branch-instructions,branch-misses ./main 2 1000
    
done