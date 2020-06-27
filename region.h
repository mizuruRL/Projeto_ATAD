typedef struct region{
    char name[40];
    char capital[40];
    int population;
    float area;
} Region;

Region createRegion(char* name, char* capital, float area, int population);

void printRegion(Region r);