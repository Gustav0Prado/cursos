#!/bin/bash

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make purge
make

for N in 1 2 3
do    
    for O in L3 L2CACHE FLOPS_DP
    do   
        FILE=${O}_${N}
        ./perfctr 3 $O ./matmult -n $N > ./saida/$FILE.txt
    done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

#teste de cut da saida: cat ./saida/L3_1.txt | grep "DP MFLOP/s" | rev | cut -c 3- | sed 's/\s.*$//'