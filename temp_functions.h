#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define defaultFile "temper_data.csv" // файл по умолчанию
struct programm
{
    char *fileName; // название csv файла для открытия
    long int csvLen; // длина строки из csv файла
    long int numberLine; // количество строк в csv файле (количество структур)
    _Bool mounth; // месяц
} settings;

struct dataTemp
{
    uint16_t year;
    uint8_t mounth;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
};

char *readFile(char *name);
struct dataTemp *temperCsv(char *csv);
void printTempStruct(struct dataTemp *statistic, int line);