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
#include "patient.h"


typedef char String[255];

int equalsStringIgnoreCase(char str1[], char str2[]);
void printCommandsMenu();

int main(int argc, char** argv) {

	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit) {
		
		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';
        
		if (equalsStringIgnoreCase(command, "QUIT")) {
			quit = 1;
			printf("Goodbye!\n");			
		}
		else if (equalsStringIgnoreCase(command, "LOAD")) {
			commandLoad();
		}
		else if (equalsStringIgnoreCase(command, "LOADR")) {
			commandLoadR();
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			commandClear();
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE")) {
			commandAverage();
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW")) {
			commandFollow();
		}
		else if (equalsStringIgnoreCase(command, "SEX")) {
			commandSex();
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			commandShow();
		}
		else if (equalsStringIgnoreCase(command, "TOP5")) {
			commandTop5();
		}
		else if (equalsStringIgnoreCase(command, "OLDEST")) {
			commandOldest();
		}
		else if (equalsStringIgnoreCase(command, "GROWTH")) {
			commandGrowth();
		}	
		else if (equalsStringIgnoreCase(command, "MATRIX")) {
			commandMatrix();
		}
		else if (equalsStringIgnoreCase(command, "REGIONS")) {
			commandRegions();
		}	
		else if (equalsStringIgnoreCase(command, "REPORT")) {
			commandReport();
		}
		else {
			printf("%s : Comando não encontrado.\n", command);
		}
	}

	/* libertar memória e apresentar mensagem de saída. */

	return (EXIT_SUCCESS);
}

int equalsStringIgnoreCase(char* str1, char* str2) {
	return (strcasecmp(str1, str2) == 0);
}

void printCommandsMenu() {
	system("clear");
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOAD, LOADR,CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, RELEASED, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORTS)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}
