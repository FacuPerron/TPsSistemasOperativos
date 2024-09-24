#!/bin/bash
user=$(whoami)
diaActual=$(date +%A)
numeroDia=$(date +%e)
mes=$(date +%B)
anio=$(date +%G)
diaDelAnio=$(date +%j)



diasFaltantes(){
	ans=$(($1-$2))
	echo $ans
}

faltan=$(diasFaltantes 365 $diaDelAnio)

diaDeFechaIngresada=$(date -d 03/18/2023 +%j)

faltanteIngresada=$(diasFaltantes 365 $diaDeFechaIngresada)

echo "Hola $1, Ud. esta logueado como usuario $user!"
echo "Hoy es $diaActual, $numeroDia de $mes de $anio."
echo "Faltan $faltan dias para que termine el año $anio."
echo "Si hoy fuera 03/18/2023, faltaría $faltanteIngresada para que termine el $anio."