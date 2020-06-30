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
 * @file key.h
 * @author André Dias, Tomás Barroso
 * @brief Defines a key for the Regions map. Key contains a string.
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

typedef struct keyString{
    char content[255];
}KeyString;

/**
 * @brief Creates a Key
 * 
 * @param cntnt 
 * @return KeyString Key
 */
KeyString createKey(char *cntnt);