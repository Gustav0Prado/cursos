#!/usr/bin/python3

import subprocess, os, sys, generate, statistics

os.system('make clean && make')

inp = "tsp"
if "-g" in sys.argv:
   pos = sys.argv.index("-g")+1
   generate.generateExample( int(sys.argv[pos]), int(sys.argv[pos+1]), int(sys.argv[pos+2]) )

if ("-g" in sys.argv) or ("-e" in sys.argv):
   inp = "simple"

if "-r" in sys.argv:
   ran = int(sys.argv[sys.argv.index("-r")+1])
else:
   ran = 20

dir = subprocess.check_output(['pwd']).decode()[:-1]

timeSeq = []
timePar = []

lastResult = []

print(f"\nSequencial")
for i in range(ran):
   result = subprocess.run(f"TIMEFORMAT=%5R; time {dir}/tsp < {inp}.in", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, executable='/bin/bash')
   r = result.stdout.strip().decode().replace("\n", ", ")
   if len(lastResult) > 0 and r != lastResult:
         print("Resultados inconsistentes!!!\n")
         exit(-1)
   lastResult = r
   timeSeq.append( float(result.stderr.decode()[:-1].replace(",", "."))  )

print(f"Tempo em segundos (Media) : {statistics.mean(timeSeq)}")
print(f"Resultado: \n{lastResult}")

print(f"\nParalelo")
for t in [2,4,8,16]:
   for i in range(ran):
      result = subprocess.run(f"export OMP_NUM_THREADS={t};TIMEFORMAT=%5R; time {dir}/tsp-par < {inp}.in", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, executable='/bin/bash')
      r = result.stdout.strip().decode().replace("\n", ", ")
      if len(lastResult) > 0 and r != lastResult:
            print("Resultados inconsistentes!!!")
            exit(-1)
      lastResult = r
      timePar.append( float(result.stderr.decode()[:-1].replace(",", "."))  )

   print(f"Tempo em segundos (Media) com {t} threads : {statistics.mean(timePar)}")
   print(f"Resultado: \n{lastResult}")