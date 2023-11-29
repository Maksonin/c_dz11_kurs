#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "temp_functions.h"

// gcc main.c -o main
// ./main -f data/temperature_small.csv 

void doit(){
     printf("DoIT!\n");
    char *csv;

    if(settings.fileName)
        csv = readFile(settings.fileName);
    else{
        printf("The program didn't  recieve -f parametr. Change default file\n");
        csv = readFile(defaultFile);
    }
    if(!csv){
        printf("Error! The CSV file is missing!\n");
        exit(0);
    }
    
    struct dataTemp *statistic = temperCsv(csv);
    
    // printf(" %d \n", statistic[0].temperature);
    int month = 2;
    if(month == 2){
        for(int i = 0; i < settings.numberLine; i++){
            if(statistic[i].mounth == month)
                printf("t-%d\n",statistic[i].temperature);
        }
    }
}

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
    
    while((rez = getopt(argc, argv,"hf:m::")) != -1 ){
        switch (rez)
        {
        case 'h': printf("found argument \"a\" \n"); break;
        case 'f': printf("found argument \"b = %s\" \n", optarg); settings.fileName = optarg; break;
        case 'm': printf("found argument \"C = %s\" \n", optarg); settings.mounth = optarg; break;
        case '?': printf("No param \n"); doit(); break;
        default:
            break;
        }
    }
    
    doit();

    return 0;
}