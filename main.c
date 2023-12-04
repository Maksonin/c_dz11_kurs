#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "temp_functions.h"

int main(int argc, char **argv){
    int rez = 0;
    char *fileN = 0;
    int month = 0;
    _Bool listAll = 0;
    int nParam = 0;
    
    while((rez = getopt(argc, argv,"hm:f:l")) != -1 ){
        switch (rez)
        {
        case 'h': 
            printHelp(); 
            break;
        case 'f': 
            fileN = optarg; 
            nParam++;
            break;
        case 'm': 
            month = atoi(optarg); 
            nParam++;
            break;
        case 'l': 
            listAll = 1;
            nParam++;
            break;
        default:
            printHelp();
            break;
        }
    }

    if(nParam)
        getStatistic(fileN, month, listAll);
    else
        printHelp();

    return 0;
}