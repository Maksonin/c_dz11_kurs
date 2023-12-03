#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define defaultFile "temper_data.csv" // файл по умолчанию


static char *fileName; // название csv файла для открытия
static long int csvLen; // длина строки из csv файла
static long int numberLine; // количество строк в csv файле (количество структур)
static _Bool month; // месяц


typedef struct 
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
} dataTemp;

typedef struct {
    dataTemp *data;
    int size;
    int sp;
} stack;

void getStatistic(char *fileN, int month);
void printStatistic(stack *statistic, int month);
stack *temperCsv(char *csv);
char *readFile(char *name);
void printTempStruct(dataTemp *statistic, int start, int end);
void init_stack(stack *st);
void push (stack *st, dataTemp *value);

#endif