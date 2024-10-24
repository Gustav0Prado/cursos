inverteNum::Int->Int
inverteNum 0 = 0
inverteNum n = 10^(numDigito n - 1)*(mod n 10)+(inverteNum (div n 10))

numDigito::Int->Int
numDigito n
   |(div n 10 == 0) = 1
   |otherwise = (numDigito (div n 10))+1

somaElem::[Int]->Int
somaElem [] = 0
somaElem (a:x) = a+(somaElem x)

somatorio::Int->Int
somatorio 0 = 0
somatorio n = n+(somatorio (n-1))

inverte::[Int]->[Int]
inverte [] = []
inverte (a:x) = (inverte x)++[a]

ocorre::Int->Int->Int
ocorre n x
   |(div x 10 == 0 && x == n) = 1
   |(div x 10 == 0 && x /=  n) = 0
   |(n == (mod x 10)) = 1+(ocorre n (div x 10))
   |otherwise = ocorre n (div x 10)

mult::Int->Int->Int
mult x 0 = 0
mult x 1 = x
mult x y
   |(y > 0) = x+(mult x (y-1))
   |otherwise = -x+(mult x (y+1))

ncrescente::Int->[Int]
ncrescente n = [x | x <- [0..n]]

ndecrescente::Int->[Int]
ndecrescente n = [n-x | x <- [0..n]]

nparescrescente::Int->[Int]
nparescrescente n = [x | x <- [0..n], mod x 2 == 0]

nparesdecrescente::Int->[Int]
nparesdecrescente n = [n-x | x <- [0..n], mod x 2 == 0]

fatduplo::Int->Int
fatduplo 0 = 1
fatduplo n
   |(mod n 2 == 1) = n*(fatduplo (n-1))
   |otherwise = fatduplo (n-1)

fat::Int->Int
fat 0 = 1
fat n = n*(fat (n-1))

superfat::Int->Int
superfat 0 = 1
superfat n = fat(n)*(superfat (n-1))

menor::[Int]->Int
menor [a] = a
menor (a:x)
   |(a < menor x) = a
   |otherwise = menor x

binario::Int->Int
binario 0 = 0
binario a = 10*(binario (div a 2))+(mod a 2)

soma::Int->Int->Int
soma a 0 = a
soma a b = 1+(soma a (b-1))

somaDig::Int->Int
somaDig 0 = 0
somaDig a = (mod a 10)+(somaDig (div a 10))