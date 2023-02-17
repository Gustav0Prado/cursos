   #!/bin/bash

echo "performance" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor

make clean -C ./v1
make -C ./v1

make clean -C ./v2
make -C ./v2

rm -f ./saida/*.txt
rm -f ./saida/*.dat
rm -f ./saida/done-v1
rm -f ./saida/done-v2

#pega core mais isolado da CPU
CORES=$(likwid-topology | grep Cores | cut -c 19-)
let CORES--

#prepara arquivos de plot
for O in L3 Tempo L2CACHE FLOPS_DP-AVX FLOPS_DP-SSE
do
   echo "# Marcador "v1" $O"  >> ./saida/plot_$O-v1.dat
   echo "# n op1 op2" >> ./saida/plot_$O-v1.dat

   echo "# Marcador "v2" $O"  >> ./saida/plot_$O-v2.dat
   echo "# n op1 op2" >> ./saida/plot_$O-v2.dat
done

#Loop de testes
for V in v1 v2
do
   for O in L3 L2CACHE FLOPS_DP
   do   
      echo "Executando teste de $O - $V"
      for N in 32 64 #128 256 512 1000 2000 4000 8000
      do
         printf "\tExecutando teste para N = $N\n"    
         FILE=${O}_${N}_${V}
         ./perfctr $CORES $O ./$V/cgSolver -i 150 -p 0 -o ./$V/saida$N.txt -n $N -k 7 > ./saida/$FILE.txt

         case $O in

         L3)
               RES=$(cat ./saida/$FILE.txt | grep "L3 bandwidth" | sed 's/[^0-9.]*//g' | sed 'N;s/\n/ /')

               echo "$N $RES" >> ./saida/plot_$O-$V.dat
               ;;

         L2CACHE)
               RES="$(cat ./saida/$FILE.txt | grep "miss ratio" | sed 's/[^0-9.]*//g' | sed 'N;s/\n/ /')"
               
               echo "$N $RES" >> ./saida/plot_$O-$V.dat
               ;;

         FLOPS_DP)
               #separa saida avx e sse
               AVX="$(cat ./saida/$FILE.txt | grep "MFLOP/s" | sed 's/[^0-9.]*//g' | sed -n 'n;p' | sed 'N;s/\n/ /')"
               SSE="$(cat ./saida/$FILE.txt | grep "MFLOP/s" | sed 's/[^0-9.]*//g' | sed -n 'p;n' | sed 'N;s/\n/ /')"

               echo "$N $AVX" >> ./saida/plot_$O-AVX-$V.dat

               echo "$N $SSE" >> ./saida/plot_$O-SSE-$V.dat
               ;;

         esac
      done
      touch ./saida/done-$V
   done
done

echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
