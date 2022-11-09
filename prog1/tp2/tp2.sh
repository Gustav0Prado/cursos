ls /home/bcc | #lista  usuarios de bcc
xargs finger | #passa cada usuario como argumento para finger 
grep Name | #seleciona a parte com o nome
cut -b 32- | #corta tudo antes do nome
cut -d " " -f 1 | #corta tudo depois do primeiro espaço (deixa o primeiro nome)
tr [:lower:] [:upper:] | #deixa tudo em maiuscula
sort -u > nomes_de_informatas.txt  #remove duplicados e salva no arquivo txt

echo 'nomes mais usados: ' >> nomes_de_informatas.txt #separar as duas seções

ls /home/bcc | #lista  usuarios de bcc
xargs finger | #passa cada usuario como argumento para finger 
grep Name | #seleciona a parte com o nome
cut -b 32- | #corta tudo antes do nome
cut -d " " -f 1 | #corta tudo depois do primeiro espaço (deixa o primeiro nome)
tr [:lower:] [:upper:] | #deixa tudo em maiuscula
sort | uniq -c | #conta ocorrencias
sort -nr | #organiza numericamente e do maior para o menor (reverso)
head >> nomes_de_informatas.txt #seleciona os 10 primeiros e grava no fim do arquivo
