#!/bin/bash

#funções do programa


#função para criar lista ordenada com a coulna dada em $1
crialista(){
	cat * | cut -d';' -f$2 | tr [:lower:] [:upper:] | sed "s/---------------//g" | sed '/^[[:space:]]*$/d' | sort | uniq -c | sort -nr > $1
}

converte_arqs(){
i=0
for file in *   #conversão para utf-8
do
   if [ $i -eq 0 ]
   then
      #converte para UTF-8 e salva com o mesmo nome
      echo "convertendo $file para UTF-8..."
      echo "$(iconv -f WINDOWS-1252 -t UTF-8 "$file" | tr -d '\0')" > "$file"
   fi
done
i=1   #executa conversão apenas uma vez
}



#programa principal

echo "baixando indice..."
wget -q -nc http://dadosabertos.c3sl.ufpr.br/curitiba/156 -O index.html    #baixa index se n tiver
csvs=$(cat index.html |  grep -o "2021.*csv" | grep -v "Historico\|_201"  | cut -b -34) #var com nomes dos arquivos

echo "procurando e baixando os arquivos..."
for i in $csvs
do
	#transforma o nome dos arquivos em comandos de download
	url="wget -q -nc http://dadosabertos.c3sl.ufpr.br/curitiba/156/"  #comeco
	diretorio=" -P ./156/ &&"                                         #fim
	download=$(echo $i | sed "s,^,$url," | sed "s,$,$diretorio,")     #comeco-nomearq-fim
	$download
done

cd ./156/   #muda para o dir 156/

converte_arqs    #chama função de conversão

echo "criando listas..."
crialista assunto.txt 6
crialista subdivisao.txt 7
echo "pronto!"
ls
