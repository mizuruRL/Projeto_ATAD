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
 * @file region.h
 * @author André Dias, Tomás Barroso
 * @brief Defines the Region data type and corresponding functions
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

typedef struct region{
    char name[40];
    char capital[40];
    int population;
    float area;
} Region;

/**
 * @brief Create a Region object
 * 
 * @param name String with region name
 * @param capital String with capital name
 * @param area Float value with area
 * @param population Integer value with population
 * @return Region 
 */
Region createRegion(char* name, char* capital, float area, int population);

/**
 * @brief Prints a region object with format:
 * 
 * Region: <name> 
 * Capital: <capital>
 * Population: <population>
 * Area: <area>
 * 
 * @param r Region to print
 */
void printRegion(Region r);