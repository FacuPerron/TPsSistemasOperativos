#!/bin/bash

echo Archivo: $1
man $1 > manfile.txt 
echo lineas: $(wc -l manfile.txt)
echo palabras: $(wc -w manfile.txt)
echo caracteres: $(wc -m manfile.txt)

cat manfile.txt | sed 's/^[ \t]*//' | grep -i -E '^[e,a,i,o,u]' > vocales.txt
echo Archivo contiene vocales:
echo lineas: $(wc -l vocales.txt)
echo palabras: $(wc -w vocales.txt)
echo caracteres: $(wc -m vocales.txt)

cat manfile.txt | sed 's/^[ \t]*//' |grep '^[0-9]' > numeros.txt
echo Archivo contiene numeros:
echo lineas: $(wc -l numeros.txt)
echo palabras: $(wc -w numeros.txt)
echo caracteres: $(wc -m numeros.txt)