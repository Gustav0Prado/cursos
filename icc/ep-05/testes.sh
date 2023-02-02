#!/bin/bash

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make purge
make

#pega core mais isolado da CPU
CORES=$(likwid-topology | grep Cores | cut -c 19-)
let CORES--

#prepara arquivos de plot
for O in L3 Tempo L2CACHE FLOPS_DP-AVX FLOPS_DP-SSE
do
    echo "# Marcador "MatRowVet" $O"  >> ./saida/plot_MatRowVet-$O.dat
    echo "# n sem_otimz. com_otimiz." >> ./saida/plot_MatRowVet-$O.dat

    echo "# Marcador "MatMatRow" $O"  >> ./saida/plot_MatMatRow-$O.dat
    echo "# n sem_otimz. com_otimiz." >> ./saida/plot_MatMatRow-$O.dat
done

#Loop de testes
for O in L3 L2CACHE FLOPS_DP
do   
    echo "Executando teste de $O"
    for N in 64 100 128 1024 #2000 2048 3000 4000 5000
    do
        printf "\tExecutando teste para N = $N\n"    
        FILE=${O}_${N}
        ./perfctr $CORES $O ./matmult -n $N > ./saida/$FILE.txt

        case $O in

        L3)
            RES=$(cat ./saida/$FILE.txt | grep "L3 bandwidth" | sed 's/[^0-9.]*//g' | sed 'N;s/\n/ /')
            TEMPO="$(cat ./saida/$FILE.txt | grep "Runtime (RDTSC)" | sed 's/[^0-9.]*//g' | sed 'N;s/\n/ /')"

            #separa saida dos arquivos
            #IFS=$'\n' read -r -d '' -a resL3 <<< "$RES"
            mapfile -t resL3 <<< "$RES"
            echo "$N ${resL3[0]}" >> ./saida/plot_MatRowVet-$O.dat
            echo "$N ${resL3[1]}" >> ./saida/plot_MatMatRow-$O.dat

            #escreve saidas dos tempos
            mapfile -t resTempo <<< "$TEMPO"
            echo "$N ${resTempo[0]}" >> ./saida/plot_MatRowVet-Tempo.dat
            echo "$N ${resTempo[1]}" >> ./saida/plot_MatMatRow-Tempo.dat
            ;;

        L2CACHE)
            RES="$(cat ./saida/$FILE.txt | grep "miss ratio" | sed 's/[^0-9.]*//g' | sed 'N;s/\n/ /')"
            
            #separa saida dos arquivos
            mapfile -t resL2 <<< "$RES"
            echo "$N ${resL2[0]}" >> ./saida/plot_MatRowVet-$O.dat
            echo "$N ${resL2[1]}" >> ./saida/plot_MatMatRow-$O.dat
            ;;

        FLOPS_DP)
            #separa saida avx e sse
            AVX="$(cat ./saida/$FILE.txt | grep "MFLOP/s" | sed 's/[^0-9.]*//g' | sed -n 'n;p' | sed 'N;s/\n/ /')"
            SSE="$(cat ./saida/$FILE.txt | grep "MFLOP/s" | sed 's/[^0-9.]*//g' | sed -n 'p;n' | sed 'N;s/\n/ /')"

            mapfile -t resAVX <<< "$AVX"
            echo "$N ${resAVX[0]}" >> ./saida/plot_MatRowVet-$O-AVX.dat
            echo "$N ${resAVX[1]}" >> ./saida/plot_MatMatRow-$O-AVX.dat

            mapfile -t resSSE <<< "$SSE"
            echo "$N ${resSSE[0]}" >> ./saida/plot_MatRowVet-$O-SSE.dat
            echo "$N ${resSSE[1]}" >> ./saida/plot_MatMatRow-$O-SSE.dat
            ;;

        esac
    done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
