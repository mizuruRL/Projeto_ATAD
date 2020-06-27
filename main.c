/* PROJETO  ATAD 2019-20
* Identificacao dos Alunos:
*
*      Numero: 190221068 | Nome: André Dias
*      Numero: 190221029 | Nome: Tomás Barroso
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "project.h"


typedef char String[255];

int main(int argc, char** argv){
    String command;
	int quit = 0;
	PtList patients = NULL;
	PtMap regions = NULL;

	setlocale(LC_ALL, "PT");
	while (!quit) {
		
		menu();
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT")) {
			quit = commandQuit(&patients, &regions); /* vai provocar a saída do interpretador */				
		}
		else if (equalsStringIgnoreCase(command, "LOADP")) {
			commandLoadP(&patients);
		}
		else if (equalsStringIgnoreCase(command, "LOADR")) {
			/* invocação da função responsável pela respetiva
			funcionalidade. Remover printf seguinte após implementação */
			commandLoadR(&regions);
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			commandClear(patients, regions);
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE")) {
			printf("Comando AVERAGE nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW")) {
			printf("Comando FOLLOW nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "SEX")) {
			printf("Comando SEX nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			printf("Comando SHOW nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "TOP5")) {
			printf("Comando TOP5 nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "OLDEST")) {
			printf("Comando OLDEST nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "GROWTH")) {
			printf("Comando GROWTH nao implementado.\n");
		}	
		else if (equalsStringIgnoreCase(command, "MATRIX")) {
			printf("Comando MATRIX nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "REGIONS")) {
			printf("Comando REGIONS nao implementado.\n");
		}	
		else if (equalsStringIgnoreCase(command, "REPORT")) {
			printf("Comando REPORT nao implementado.\n");
		}
		else {
			printf("%s : Comando não encontrado.\n", command);
		}
	}
	
	return (EXIT_SUCCESS);
}
