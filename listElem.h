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
 * @file listElem.h
 * @brief Defines the type ListElem.
 * 
 * The ListElem is an alias to the type of elements 
 * held by an instance of the ADT List (PtList).
 * 
 * This alias must be changed according to the use-case.
 * 
 * @author Bruno Silva (brunomnsilva@gmail.com)
 * @bug No known bugs.
 */

#pragma once
#include "patient.h"
/** Type definition. Change according to the use-case. */
typedef Patient ListElem;

/**
 * @brief Prints an element.
 * 
 * Must be implemented according to type
 * of defined for ListElem.
 * 
 * @param elem [in] element to print
 */
void listElemPrint(ListElem elem);