#!/bin/bash

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make purge
make

#pega core mais isolado da CPU
CORES=$(likwid-topology | grep Cores | cut -c 19-)
let CORES--

#prepara arquivos de plot
for O in L3 # L2CACHE FLOPS_DP
do
    echo "# Marcador "matRowVet"" >> ./saida/plot_MatRowVet-$O-u.dat
    echo "# Marcador "matRowVet"" >> ./saida/plot_MatRowVet-$O-o.dat
    echo "# n $O (sem otimização)" >> ./saida/plot_MatRowVet-$O-u.dat
    echo "# n $O (com otimização)" >> ./saida/plot_MatRowVet-$O-o.dat
done

#Loop de testes
for N in 64 100 128 1024
do
    echo "Executando para N = $N"
    for O in L3 #L2CACHE FLOPS_DP
    do   
        printf "\tExecutando teste de $O\n"
        FILE=${O}_${N}
        ./perfctr $CORES $O ./matmult -n $N > ./saida/$FILE.txt

        case $O in

        L3)
            RES="$(cat ./saida/$FILE.txt | grep "L3 bandwidth" | rev | cut -c 3- | sed 's/\s.*$//' | rev)"
            TEMPO="$(cat ./saida/$FILE.txt | grep "Runtime (RDTSC)" | rev | cut -c 3- | sed 's/\s.*$//' | rev)"
            ;;

        L2CACHE)
            RES="$(cat ./saida/$FILE.txt | grep "miss ratio" | rev | cut -c 3- | sed 's/\s.*$//' | rev)"
            ;;

        FLOPS_DP)
            RES="$(cat ./saida/$FILE.txt | grep "MFLOP/s" | rev | cut -c 3- | sed 's/\s.*$//' | rev)"
            ;;

        esac

        #separa saida dos arquivos
        resultados=($RES)
        echo "$N ${resultados[0]}" >> ./saida/plot_MatRowVet-$O-u.dat
        echo "$N ${resultados[1]}" >> ./saida/plot_MatRowVet-$O-o.dat
        echo "$N ${resultados[2]}" >> ./saida/plot_MatMatRow-$O-u.dat
        echo "$N ${resultados[3]}" >> ./saida/plot_MatMatRow-$O-o.dat

        tempos=($TEMPO)
        echo "$N ${tempos[0]}" >> ./saida/plot_MatRowVet-Tempo-u.dat
        echo "$N ${tempos[1]}" >> ./saida/plot_MatRowVet-Tempo-o.dat
        echo "$N ${tempos[2]}" >> ./saida/plot_MatMatRow-Tempo-u.dat
        echo "$N ${tempos[3]}" >> ./saida/plot_MatMatRow-Tempo-o.dat
    done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

#executa plot das saidas
pushd ./saida > /dev/null
# ./plotFLOPS_MatVet.gp
# ./plotL2_MatVet.gp
./plotL3_MatVet.gp
./plotTempo_MatVet.gp
popd > /dev/null

#teste de cut da saida: cat ./saida/L3_1.txt | grep "L3 bandwidth" | rev | cut -c 3- | sed 's/\s.*$//' | rev
#tamanho de cache da cpu: likwid-topology | grep Size | cut -c 9- |  grep -v MB | cut -c -3
#numero de cores do pc: likwid-topology | grep Cores | cut -c 19-
