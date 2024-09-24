#!/bin/bash
#COMO SACAR LA HORA DE INICIO DE SESION
vector=($(who am i))

echo "${vector[2]}"
echo "${vector[3]}"