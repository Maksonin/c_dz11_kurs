#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "temp_functions.h"

// gcc main.c -o main
// ./main -f data/temperature_small.csv 

/* Приложение должно обрабатывать аргументы командной строки:
минимальный набор поддерживаемых ключей:
● -h Описание функционала приложения. Список ключей, которые
обрабатывает данное приложение и их назначение
● -f <filename.csv> входной файл csv для обработки. Если на задан, то файл по умолчанию
● -m <номер месяца> если задан данный ключ, то выводится только статистика
за указанный месяц, если не задан, то за год
● если нет параметров, то выдается help
 */
int main(int argc, char **argv){
    int rez = 0;
    char *fileN = 0;
    int month = 0;
    int nParam = 0;
    
    while((rez = getopt(argc, argv,"hf:m::")) != -1 ){
        switch (rez)
        {
        case 'h': 
            printf("found argument \"h\" \n"); 
            printHelp(); 
            break;
        case 'f': 
            printf("found argument \"f = %s\" \n", optarg); 
            fileN = optarg; 
            nParam++;
            break;
        case 'm': 
            printf("found argument \"m = %s\" \n", optarg); 
            month = atoi(optarg); 
            nParam++;
            break;
        default:
            printHelp();
            break;
        }
    }

    if(nParam)
        getStatistic(fileN, month);
    else
        printHelp();

    return 0;
}