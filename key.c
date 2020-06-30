/* PROJETO  ATAD 2019-20
* Identificacao dos Alunos:
*
*      Numero: 190221068 | Nome: André Dias
*      Numero: 190221029 | Nome: Tomás Barroso
*      Turma: EI-01
* Professora PL:
*
*       Patrícia Macedo
*/

/**
 * @file key.c
 * @author André Dias, Tomás Barroso
 * @brief Implements functions from key.h
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <string.h>
#include "key.h"

KeyString createKey(char *cntnt) {
    KeyString string;
    strcpy(string.content, cntnt);
    return string;
}