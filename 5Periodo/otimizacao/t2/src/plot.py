#!/usr/bin/python3

import matplotlib.pyplot as plt
import subprocess, os

min_num = 20
max_num = 25


if os.path.exists("saida/compara_Bdada.out"):
   os.remove("saida/compara_Bdada.out")
if os.path.exists("saida/compara_Bcriada.out"):
   os.remove("saida/compara_Bcriada.out") 

for i in range(min_num, max_num):
   subprocess.run(['src/geraEx.py' , str(i), str(3*i), str(i-10)])

   with open('exemplos/exRand.in') as infile:
      with open('saida/compara_Bdada.out', "a+") as outfile:
         subprocess.run(['./separa' , '-a'], stdin=infile, stderr=outfile, stdout=subprocess.DEVNULL)

      infile.seek(0)

      with open('saida/compara_Bcriada.out', "a+") as outfile:
         subprocess.run(['./separa'], stdin=infile, stderr=outfile, stdout=subprocess.DEVNULL)

y1 = []
y2 = []
y3 = []
y4 = []
x  = []
for i in range(min_num, max_num):
   x.append(i)

with open('saida/compara_Bdada.out', "r") as file:
   for line in file:
      line = line.split()
      y1.append(float(line[0]))
      y2.append(float(line[1]))

with open('saida/compara_Bcriada.out', "r") as file:
   for line in file:
      line = line.split()
      y3.append(float(line[0]))
      y4.append(float(line[1]))


plt.figure()
ax = plt.subplot(111)
ax.set_yscale('log')

plt.xlabel("Número de heróis")

plt.plot(x, y1, label = "Nós Bdada")
plt.plot(x, y2, label = "Tempo Bdada")
  

plt.plot(x, y3, label = "Nós Bcriada")
plt.plot(x, y4, label = "Tempo Bcriada")

plt.title('Bdada X Bcriada')
  
# show a legend on the plot
plt.legend()
  
# function to show the plot
plt.show()