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
 * @file region.c
 * @author André Dias, Tomás Barroso
 * @brief Provides implementation for functions defined in region.h
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "region.h"

Region createRegion(char* name, char* capital, float area, int population){
    Region region;
    strcpy(region.name, name);
    strcpy(region.capital, capital);
    region.area = area;
    region.population = population;
    return region;
}

void printRegion(Region r) {
    printf("Region: %s\nCapital: %s\nPopulation: %d\nArea: %.02f\n",r.name, r.capital, r.population, r.area);
}