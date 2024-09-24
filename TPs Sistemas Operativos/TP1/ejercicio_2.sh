#!/bin/bash

sumar(){
	aux=$(($1+$2))
	echo $aux
}

if test -d $1; then 
	cd $1
	vectorArchivos=($(ls))
	cant_Archivos=$(ls | wc -l)
	aux=$(stat -c %B ${vectorArchivos[0]}) 
	for((i=1;i<$cant_Archivos;i++))
		do
		aux=$(sumar $aux $(stat -c %B ${vectorArchivos[i]}))
	done
	
	echo "Total directorio $1 = $aux."
	
else
	echo "$1 no es un directorio valido, ingrese uno correcto:"
fi 