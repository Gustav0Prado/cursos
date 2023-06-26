#!/usr/bin/python3

def compl(a, b):
   d = list(b).copy()

   if a[0] in b:
      d.remove(a[0])
      d.append(a[1])
   
   else:
      d.remove(a[1])
      d.append(a[0])
   
   return tuple(d)

choices = []
left = []
right = []
pairs = set()
triangle = set()

# Le n, k e m da entrada padrão
inp = input().split()
n = int(inp[0])
k = int(inp[1])
m = int(inp[2])

# Le os k conflitos
for i in range(k):
   inp = input().split()

   index0 = int(inp[0])
   index1 = int(inp[1])

   # Inclui conflito na lista do primeiro heroi citado
   if(index0 < index1):
      pairs.add(tuple([index0, index1]))
   else:
      pairs.add(tuple([index1, index0]))

print((pairs))

p = list(pairs)


t = 0

for i in p:
   for j in p[p.index(i):]:
      # Se algum de membro de p[j] está em p[i], verifica se o complemento dos dois
      # também está na lista
      if any(x in j for x in i):
         c = compl(i, j)
         if c in p:
            t += 1

            p.remove(i)
            p.remove(j)
            p.remove(c)

            break


print(t)