#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void clean(){
    system("clear");
}

void commandLoad(){
    clean();
    char* filename; 
    printf("Please write only the file name\n> ");
    scanf("%s", filename);
    strncat(filename, ".csv", 4);
    FILE *file;
    int n = 10;
    char str[n];
    if(fopen(filename, "r")){
	    file = fopen(filename, "r");
        if(fgets(str,n,file)!=";"){ 
            puts(str);
        }
    }else{
        printf("file not found");
    }
    fclose(file);     
}

void commandLoadR(){
    
}

void commandClear(){
    
}

void commandAverage(){
    
}

void commandFollow(){
    
}

void commandSex(){
    
}

void commandShow(){
    
}

void commandTop5(){
    
}

void commandOldest(){
    
}

void commandGrowth(){

}

void commandMatrix(){
    
}

void commandRegions(){
    
}

void commandReport(){
    
}

/*char* load_csv(char* line, int num){

	char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}*/