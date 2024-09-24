#!/bin/bash

ps

cd /

find -name "c*" > $1 & echo "Se esta generando una lista de archivos que comienzan con c" & ps 


echo "Ingrese el id del proceso de busqueda de archivos que inician con letra c:"
read pidProceso
kill -9 $pidProceso
