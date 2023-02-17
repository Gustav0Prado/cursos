   #!/bin/bash

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make clean -C ./v1
make -C ./v1

rm -f ./saida/*.txt
rm -f ./saida/*.dat

#pega core mais isolado da CPU
CORES=$(likwid-topology | grep Cores | cut -c 19-)
let CORES--

#prepara arquivos de plot
for O in L3 Tempo L2CACHE FLOPS_DP-AVX FLOPS_DP-SSE
do
   echo "# Marcador "op1" $O"  >> ./saida/plot_op1-$O.dat
   echo "# n sem_otimz. com_otimiz." >> ./saida/plot_op1-$O.dat

   echo "# Marcador "op2" $O"  >> ./saida/plot_op2-$O.dat
   echo "# n sem_otimz. com_otimiz." >> ./saida/plot_op2-$O.dat
done

#Loop de testes
for V in v1
do
   for O in L3 L2CACHE FLOPS_DP
   do   
      echo "Executando teste de $O - $V"
      for N in 32 64 128 256 512 1000 2000 4000 8000
      do
         printf "\tExecutando teste para N = $N\n"    
         FILE=${O}_${N}_${V}
         ./perfctr $CORES $O ./$V/cgSolver -i 150 -p 0 -o ./$V/saida$N.txt -n $N -k 7 > ./saida/$FILE.txt

         case $O in

         L3)
               RES=$(cat ./saida/$FILE.txt | grep "L3 bandwidth" | sed 's/[^0-9.]*//g')
               TEMPO="$(cat ./saida/$FILE.txt | grep "Runtime (RDTSC)" | sed 's/[^0-9.e-]*//g' | cut -c2- | paste -d " "  - - | tr " " "\n")"

               #separa saida dos arquivos
               #IFS=$'\n' read -r -d '' -a resL3 <<< "$RES"
               mapfile -t resL3 <<< "$RES"
               echo "$N ${resL3[0]}" >> ./saida/plot_op1-$O.dat
               echo "$N ${resL3[1]}" >> ./saida/plot_op2-$O.dat

               #escreve saidas dos tempos
               mapfile -t resTempo <<< "$TEMPO"
               echo "$N ${resTempo[0]}" >> ./saida/plot_op1-Tempo.dat
               echo "$N ${resTempo[1]}" >> ./saida/plot_op2-Tempo.dat
               ;;

         L2CACHE)
               RES="$(cat ./saida/$FILE.txt | grep "miss ratio" | sed 's/[^0-9.]*//g' | sed 'N;s/\n/ /')"
               
               #separa saida dos arquivos
               mapfile -t resL2 <<< "$RES"
               echo "$N ${resL2[0]}" >> ./saida/plot_op1-$O.dat
               echo "$N ${resL2[1]}" >> ./saida/plot_op2-$O.dat
               ;;

         FLOPS_DP)
               #separa saida avx e sse
               AVX="$(cat ./saida/$FILE.txt | grep "MFLOP/s" | sed 's/[^0-9.]*//g' | sed -n 'n;p' | sed 'N;s/\n/ /')"
               SSE="$(cat ./saida/$FILE.txt | grep "MFLOP/s" | sed 's/[^0-9.]*//g' | sed -n 'p;n' | sed 'N;s/\n/ /')"

               mapfile -t resAVX <<< "$AVX"
               echo "$N ${resAVX[0]}" >> ./saida/plot_op1-$O-AVX.dat
               echo "$N ${resAVX[1]}" >> ./saida/plot_op2-$O-AVX.dat

               mapfile -t resSSE <<< "$SSE"
               echo "$N ${resSSE[0]}" >> ./saida/plot_op1-$O-SSE.dat
               echo "$N ${resSSE[1]}" >> ./saida/plot_op2-$O-SSE.dat
               ;;

         esac
      done
   done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
