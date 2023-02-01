#!/bin/bash

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make purge
make

CORES=$(likwid-topology | grep Cores | cut -c 19-)
let CORES--

for N in 4 8 12
do
    echo "Executando para N = $N"
    for O in L3 L2CACHE FLOPS_DP
    do   
        printf "\tExecutando teste de $O\n"
        FILE=${O}_${N}
        ./perfctr $CORES $O ./matmult -n $N > ./saida/$FILE.txt
    done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

#teste de cut da saida: cat ./saida/L3_1.txt | grep "L3 bandwidth" | rev | cut -c 3- | sed 's/\s.*$//' | rev
#tamanho de cache da cpu: likwid-topology | grep Size | cut -c 9- |  grep -v MB | cut -c -3
#numero de cores do pc: likwid-topology | grep Cores | cut -c 19-
