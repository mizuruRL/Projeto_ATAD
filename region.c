#include <stdio.h>
#include <stdlib.h>
#include "region.h"

Region createRegion(char* name, char* capital, float area){
    Region region = {name,capital,area};
    return region;
}