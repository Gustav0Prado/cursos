#!/bin/bash
pushd ../
make
popd
for f in *.in
do
	echo "Processando $f"
	name="$(echo "${f%%.*}")"
	../myht < $f > $name.out
	difer="$(diff $name.out $name.sol)"
	if [ -z "$difer"  ]
	then
		echo "$name Correto!"
	else
		echo -e "Erro $name\n $difer"
	fi
done
