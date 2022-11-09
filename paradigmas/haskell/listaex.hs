inverte::[t]->[t]
inverte [] = []
inverte (a:x) = (inverte x)++[a]

removePrim::[t]->[t]
removePrim [] = []
removePrim (a:x) = x

removeUlt::[t]->[t]
removeUlt [a] = []
removeUlt (a:x) = a:(removeUlt x)

somaPares::[Int]->Int
somaPares [] = 0
somaPares (a:x)
   | (mod a 2 == 0) = a+(somaPares x)
   | otherwise = somaPares x

somaPosPares::[Int]->Int->Int
somaPosPares [] p = 0
somaPosPares (a:x) p
   | (mod p 2 == 0) = a+(somaPosPares x (p+1))
   | otherwise = somaPosPares x (p+1)

insereN::[Int]->Int->Int->[Int]
insereN [] n m = [m]
insereN (a:x) n m
   |(n == 1) = m:a:x
   |otherwise = a:(insereN x (n-1) m)

penult::[Int]->Int
penult [] = 0
penult [p, u] = p
penult (a:x) = penult x

duplicata::[Int]->[Int]
duplicata [] = []
duplicata [a] = [a]
duplicata (a:b:x)
   |(a == b) = a:(duplicata x)
   |otherwise = a:b:(duplicata x)

divide::[Int]->Int->[Int]
divide [] n = []
divide (a:x) n
   |(n == 1) = [a]++[0]++x
   |otherwise = a:(divide x (n-1))

fatia::[Int]->Int->Int->[Int]
fatia [] n m = []
fatia (a:x) n m
   |(n <= 1 && m > 1) = a:(fatia x (n-1) (m-1))
   |(m == 1) = [a]
   |otherwise = fatia x (n-1) (m-1)

gira::[Int]->Int->[Int]
gira [] n = []
gira (a:x) n
   |(n > 0) = (gira (x++[a]) (n-1))
   |otherwise = a:x

criaInt::Int->Int->[Int]
criaInt a b = [x | x <- [a..b]]