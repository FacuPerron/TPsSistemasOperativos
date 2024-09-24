#/bin/bash

sumar(){
	aux=$(($1+$2))
	echo $aux
}
restar(){
	aux=$(($1-$2))
	echo $aux
}
multiplicar(){
	aux=$(($1*$2))
	echo $aux
}
dividir(){
	aux=$(($1/$2))
	echo $aux
}

ingresoDatos(){
	echo "Ingrese el primer numero: "
	read numero1
	echo "Ingrese el segundo numero: "
	read numero2
}


case $1 in 

	suma)
		ingresoDatos
		resultado=$(sumar $numero1 $numero2)
		echo "$numero1 + $numero2 = $resultado"
	;;
	resta)
		ingresoDatos
		resultado=$(restar $numero1 $numero2)
		echo "$numero1 - $numero2 = $resultado"
	;;
	multiplicacion)
		ingresoDatos
		resultado=$(multiplicar $numero1 $numero2)
		echo "$numero1 * $numero2 = $resultado"
	;;
	division)
		ingresoDatos
		if test $numero2 -eq 0; then
			echo "ERROR: Division por 0."
		else 
			resultado=$(dividir $numero1 $numero2)
			echo "$numero1 / $numero2 = $resultado"
		fi
	;;
	*)
		echo "Lo siento, no conozco esa operacion."
		
esac