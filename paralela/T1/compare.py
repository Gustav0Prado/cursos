#!/usr/bin/python3

import subprocess, os, sys, generate, statistics

os.system('make clean && make')

if "-g" in sys.argv:
   if len(sys.argv) != 5:
      pos = sys.argv.index("-g")+1
      generate.generateExample( int(sys.argv[pos]), int(sys.argv[pos+1]), int(sys.argv[pos+2]) )

dir = subprocess.check_output(['pwd']).decode()[:-1]

timeSeq = []
timePar = []

lastResult = []

print(f"\nSequencial")
for i in range(20):
   result = subprocess.run(f"TIMEFORMAT=%5R; time {dir}/tsp < simple.in", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, executable='/bin/bash')
   r = result.stdout.strip().decode().replace("\n", ", ")
   if len(lastResult) > 0 and r != lastResult:
         print("Resultados inconsistentes!!!\n")
         exit(-1)
   lastResult = r
   timeSeq.append( float(result.stderr.decode()[:-1].replace(",", "."))  )

print(f"Tempo em segundos (Mediana) : {statistics.median(timeSeq)}")
print(f"Resultado: \n{lastResult}")

print(f"\nParalelo")
for i in range(20):
   result = subprocess.run(f"TIMEFORMAT=%5R; time {dir}/tsp-par < simple.in", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, executable='/bin/bash')
   r = result.stdout.strip().decode().replace("\n", ", ")
   if len(lastResult) > 0 and r != lastResult:
         print("Resultados inconsistentes!!!")
         exit(-1)
   lastResult = r
   timePar.append( float(result.stderr.decode()[:-1].replace(",", "."))  )

print(f"Tempo em segundos (Mediana) : {statistics.median(timePar)}")
print(f"Resultado: \n{lastResult}")