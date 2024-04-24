proximo dia:

	corregir "tcgetattr: Inappropriate ioctl for device" (tiene algo que ver con la llamada al hide y el show de los simbolos)

	hacer pruebas locas con los argumentos desordenados y de todo
	


si hay tiempo:

	ver como personalizar un poco la minishell
		- limpiar la terminal cuando inicio
		


cosas de javier:
	fíjate en el funcionamiento de echo $*, echo $%, echo $!, etc.
	Unas veces imprime un salto de línea, otra $ y el carácter,
	otras valores extraños (por ejemplo `echo $·', el punto que hay en el 3).

	yo creo que el mejor sitio para llamar a expand_wildcard es en check_token, después de if (token[i] == '$'){...} else if (token[i] == '*'){expand_wildcard}

