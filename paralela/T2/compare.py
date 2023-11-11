#!/usr/bin/python3

import subprocess, os, sys, generate, statistics, re

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

check = True
if "-d" in sys.argv:
   check = False

dir = subprocess.check_output(['pwd']).decode()[:-1]

timeSeq = []
timeTotalPar = []
timePar = []

lastResult = []

print(f"\nSequencial Otimizado")
for i in range(ran):
   result = subprocess.run(f"{dir}/tsp < {inp}.in", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, executable='/bin/bash')
   r = result.stdout.decode().partition("\n")[0]
   if check and len(lastResult) > 0 and r != lastResult:
         print("Resultados inconsistentes!!!\n")
         exit(-1)
   lastResult = r
   timeSeq.append( float(re.findall("\d+\.\d+", result.stdout.decode())[0]) )
   timePar.append( float(re.findall("\d+\.\d+", result.stdout.decode())[1]) )

medSeq = statistics.mean(timeSeq) / 1000
medPar = statistics.mean(timePar) / 1000

if (ran > 1):
   print(f"Tempo em segundos   (Media) : {medSeq:.7f}, {statistics.stdev(timeSeq):.7f}")
else:
   print(f"Tempo em segundos   (Media) : {medSeq:.7f}")

print(f"Tempo Paralelizavel (Media) : {(medPar/medSeq):.7f}")
print(f"Resultado: {lastResult}")


print(f"\nParalelo")
for t in [2]:
   for i in range(ran):
      result = subprocess.run(f"mpirun --hostfile hosts.txt -np {t} {dir}/mpi < {inp}.in", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, executable='/bin/bash')
      r = result.stdout.decode().partition("\n")[0]
      if check and len(lastResult) > 0 and r != lastResult:
            print("Resultados inconsistentes!!!")
            exit(-1)
      lastResult = r
      timeTotalPar.append( float(re.findall("\d+\.\d+", result.stdout.decode())[0]) )

   medTotalPar = statistics.mean(timeTotalPar)

   if (ran > 1):
      print(f"Media   Ttotal  - {t} processos : {medTotalPar:.7f}, {statistics.stdev(timeTotalPar):.7f} - S(p) = {(medSeq/medTotalPar):.2f}")
   else:
      print(f"Media   Ttotal  - {t} processos: {medTotalPar:.7f} - S(p) = {(medSeq/medTotalPar):.2f}")
   print(f"Resultado: {lastResult}\n")
   timeTotalPar = []