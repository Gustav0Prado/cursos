#!/usr/bin/python3

import subprocess

MAX_NIVEL = 25
chars = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9']

def backtrack(serial, nivel):
   if (nivel == MAX_NIVEL):
      serial_key = "".join(serial[0:5]) + "-" + "".join(serial[5:10]) + "-" + "".join(serial[10:15]) + "-" + "".join(serial[15:20]) + "-" + "".join(serial[20:25])
      print(f" Testando serial = {serial_key}", end="\r")
      s = subprocess.Popen(f"echo '{serial_key}' | ./pacman | grep Erro", shell=True, stdout=subprocess.PIPE)

      if (s.stdout==""):
         return True
      else:
         return False

   else:
      for i in range(MAX_NIVEL):
         serial[nivel] = chars[i].upper()
         if (backtrack(serial, nivel+1)):
            break


licensa = ['']*25
backtrack(licensa, 0)
print(f"O serial eh: {licensa}")