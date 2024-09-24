#!/bin/bash



mkdir $1/dir1

mkdir $1/dir2

sed -n 1,10p /etc/passwd | sort -r > $1/dir1/ordenado_tp1_2023_dir1.txt

tail -n 10 /etc/passwd | sort -r > $1/dir2/ordenado_tp1_2023_dir2.txt

salida=$(wc -l /etc/passwd)
echo $salida

