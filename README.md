proximo dia:

	posible mejora muy tocha es que vayas mirando token por token y haciendo las llamadas de parseo correctas para cada token

	hacer pruebas locas con los argumentos desordenados y de todo
	


si hay tiempo:

	ver como personalizar un poco la minishell
		- limpiar la terminal cuando inicio
		

	
cosas de javier:

	Javi importante mirate los errores con todos los builtins porque son los importantes el resto ya estan todos arreglados

	-errores en general:
		*(esto no deberia depender de nosotros) esto no sé si nosotros tenemos que gestionarlo: me meto en sgoinfre y hago cd .. y me lleva a /sgoinfre/students (BASH me lleva a mi home)
	-buscar leaks y errores de free
	-Ver códigos de salida (echo $?)
		*cat NOEXISTE.txt: código BASH 1 (devolvemos 256)✅
		*rm NOEXISTE: código BASH 1 (devolvemos 256)✅
		*ls NOEXISTE: código BASH 2 (devolvemos 512)✅
		*grep: código BASH 2 (devolvemos 512)✅
		*grep kk: (se queda pensando y lo paras con ^C): BASH 130, nos 2✅
		*grep NOEXISTE README.md (no encuentra nada): BASH 1, nos 256✅
		*cd NOEXISTE: BASH 1, nos 0 ✅
		*mkdir EXISTE: BASH 1, nos 256✅
		*cd SINPERMISO: BASH 1, nos 0 ✅
		*rm DIREXISTE: BASH 1, nos 256✅
		*touch DIRSINPERMISO/test: BASH 1, nos 256✅

	-norminette