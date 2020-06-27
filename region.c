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