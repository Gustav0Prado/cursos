removek::[z]->Int->[z]
removek [] x = []
removek (a:x) n
   | (n == 1) = x
   | otherwise = a:(removek x (n-1))

fatia::[t]->Int->Int->[t]
fatia [] b c = []
fatia (a:x) b c
   | (b <= 1 && c > 1) = a:(fatia x (b-1) (c-1))
   | (c == 1) = [a]
   | otherwise = fatia x (b-1) (c-1)

intercala::[Int]->[Int]->[Int]
intercala [] [] = []
intercala [a] [] = [a]
intercala [] [b] = [b]
intercala (a:x) (b:y)
   | (a <= b) = a:(intercala x (b:y))
   | otherwise = b:(intercala (a:x) y)


--data AVL = NodoNull | NodoInt String String String Int AVL AVL deriving Show

data ListaEnc = NodoNull | NodoInt Int ListaEnc deriving Show

{-passeioPre::AVL->[String]
passeioPre NodoNull = []
--passeioPre (NodoInt a b c d NodoNull NodoNull) = [a]
passeioPre (NodoInt a b c d esq dir) = [a]++(passeioPre esq)++passeioPre(dir)-}

passeioL::ListaEnc->[Int]
passeioL NodoNull = []
passeioL (NodoInt a prox) = [a]++(passeioL prox)

somaParesL::ListaEnc->Int
somaParesL NodoNull = 0
somaParesL (NodoInt a prox)
   |(mod a 2 == 0) = a+(somaParesL prox)
   |otherwise = somaParesL prox

filtrar::(t->t->Bool)->[t]->t->[t]
filtrar f [] x = []
filtrar f (a:y) x
   | (f a x) = a:(filtrar f y x)
   | otherwise = filtrar f y x

f::Int->Int->Bool
f a x = (a >= x && a <= x*x)