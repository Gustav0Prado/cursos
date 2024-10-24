#!/usr/bin/python3

import subprocess, os, sys, generate, statistics, re

os.system('make clean && make')

remote = []
with open(r"hosts.txt", 'r') as fp:
    for count, line in enumerate(fp):
        h = str(line).strip()
        if h != "localhost": remote.append(h)

# Seta modo Perfomance
subprocess.run("echo performance > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor", shell=True, stdout=subprocess.DEVNULL)
for host in remote:
   subprocess.run(f"ssh {host} 'echo performance > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor'", shell=True, stdout=subprocess.DEVNULL)
print("\nSetado para o modo performance")

# Pega num de cores por nucleo
cores = int (subprocess.check_output("export LC_ALL=C; lscpu | awk '/^Core\(s\) per socket:/ {print $4}';", shell=True).decode())
print (f"{count+1} CPU(s) com {cores} cores")

inp = "tsp"

runSeq = True
if "-p" in sys.argv:
   runSeq = False

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

if runSeq:
   print(f"\n=> Sequencial")
   for i in range(ran):
      result = subprocess.run(f"{dir}/tsp < {inp}.in", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, executable='/bin/bash')
      r = result.stdout.decode().partition("\n")[0].strip()
      if check and len(lastResult) > 0 and r != lastResult:
            print("Resultados inconsistentes!!!\n")
            exit(-1)
      lastResult = r
      timeSeq.append( float(re.findall("\d+\.\d+", result.stdout.decode())[0]) )
      timePar.append( float(re.findall("\d+\.\d+", result.stdout.decode())[1]) )

   medSeq = statistics.mean(timeSeq) / 1000
   medPar = statistics.mean(timePar) / 1000

   if (ran > 1):
      print(f"   Tempo em segundos   (Media) : {medSeq:.7f}, {statistics.stdev(timeSeq)/1000:.7f}")
   else:
      print(f"   Tempo em segundos   (Media) : {medSeq:.7f}")

   print(f"   Tempo Paralelizavel (Media) : {(medPar/medSeq):.7f}")
   print(f"   Resultado: {lastResult}")


print(f"\n=> Paralelo")
for t in [3,5,7,9]:
   for i in range(ran):
      result = subprocess.run(f"mpirun --hostfile hosts.txt -np {t} {dir}/mpi 2> /dev/null < {inp}.in", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, executable='/bin/bash')
      r = result.stdout.decode().partition("\n")[0].strip()
      if check and len(lastResult) > 0 and r != lastResult:
            print("Resultados inconsistentes!!!")
            print(f"|{lastResult}| - |{r}|")
            exit(-1)
      lastResult = r
      timeTotalPar.append( float(re.findall("\d+\.\d+", result.stdout.decode())[0]) )

   medTotalPar = statistics.mean(timeTotalPar)

   if (runSeq):
      if (ran > 1):
         print(f"   Media   Ttotal  - {t} processos : {medTotalPar:.7f}, {statistics.stdev(timeTotalPar):.7f} - S(p) = {(medSeq/medTotalPar):.2f}")
      else:
         print(f"   Media   Ttotal  - {t} processos: {medTotalPar:.7f} - S(p) = {(medSeq/medTotalPar):.2f}")
   else:
      if (ran > 1):
         print(f"   Media   Ttotal  - {t} processos : {medTotalPar:.7f}, {statistics.stdev(timeTotalPar):.7f}")
      else:
         print(f"   Media   Ttotal  - {t} processos: {medTotalPar:.7f}")
   print(f"   Resultado: {lastResult}\n")
   timeTotalPar = []

# Volta para o modo powersave
subprocess.run("echo powersave > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor", shell=True, stdout=subprocess.DEVNULL)
for host in remote:
   subprocess.run(f"ssh {host} 'echo powersave > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor'", shell=True, stdout=subprocess.DEVNULL)
print("Setado para o modo powersave")
