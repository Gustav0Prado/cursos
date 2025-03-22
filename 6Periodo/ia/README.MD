# Inteligência Artificial (ci1209)

## 🔍 Informações
Trabalhos aqui contidos contemplam a disciplina ministrada pelo prof. Fabiano no segundo semestre de 2024 e pela prof. Aurora no primeiro semestre de 2025

### 2024
O trabalho de 2024 é basicamente reverter um estado E do [Jogo da Vida](https://pt.wikipedia.org/wiki/Jogo_da_vida) para um estado E' anterior com o mínimo possível de células. O trabalho não está 100% terminado porém já é funcional e consegue reverter algum estado dado por uma matrix n x n de números, onde 0 representa célula morta e 1 representa célula viva. O que faltou nesse trabalho foi otimizar a saída e tempo de processamento para achar a melhor resposta possíve, i.e com menor número de células vivas no estado anterior.

### 2025
Os trabalhos de 2025 são baseados nos [Projetos da Berkeley](https://inst.eecs.berkeley.edu/~cs188/fa24/) de 2024, que são basicamente métodos de busca para uma inteligência artifical no jogo do Pacman (o próprio Pacman, no caso), seguindo as instruções e arquivos base do próprio site da Berkeley.

## ▶️ Como rodar

## Game of life
Apenas compile os arquivos com o Makefile e rode o executável. Nenhuma biblioteca adicional requerida.

## Pacman
Para o pacman a única dependência é o *tkinter*, que pode ser instalado facilmente no Ubuntu (e derivados) com *sudo apt install python3-tk*.
Para rodar o Pacman em si é um pouco mais complexo, pois existe um comando para cada método de busca e subcomandos diferentes para heurísticas e etc. Recomendo dar uma olhada no site da Berkeley para ver com mais detalhes e rodar o necessário.