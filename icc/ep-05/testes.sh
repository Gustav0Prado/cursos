#!/bin/bash

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make purge
make

for N in 1 2 3
do    
    for O in L3 L2CACHE FLOPS_DP
    do   
        FILE=${O}_${N}
        ./perfctr 3 FLOPS_DP ./matmult -n $N > ./saida/$FILE.txt
    done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor