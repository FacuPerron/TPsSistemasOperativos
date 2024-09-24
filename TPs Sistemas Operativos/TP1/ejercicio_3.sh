#!/bin/bash

usuario=$(whoami)
host=$(hostname)
usuariosConectados=$(who)
fecha=$(date +%d/%m/%Y)
hora=$(date +%Hh:%Mm:%Ss)



echo "Bienvenido usuario: $usuario."
echo "Usted se ha conectado en el dia: $fecha"
echo "A la hora: $hora"
echo "En la terminal: $TERM del host $host."
echo "Se encuentran conectados en este momento, los siguientes usuarios:"
echo "$usuariosConectados"
echo "Su path es: $PATH"

