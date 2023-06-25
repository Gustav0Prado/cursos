import random

with open('exemplos/exRand.in', 'w+') as file:
   file.write("20 10 5\n")
   for i in range(15):
      file.write(f"{random.randint(1, 20)} {random.randint(1, 20)}\n")