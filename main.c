#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

// gcc main.c -o main
// ./main -f data/temperature_small.csv 

struct dataTemp
{
    uint16_t year;
    uint8_t mounth;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    int8_t temperature;
};

/* Функция вывода массива структур dataTemp с длиной line */
void printTempStruct(struct dataTemp *statistic, int line){
    for(int i = 0; i <= line; i++){
        printf("%d-%02d-%d  %02d:%02d  t=%d\n", 
            statistic[i].year,
            statistic[i].mounth,
            statistic[i].day,
            statistic[i].hour,
            statistic[i].minute,
            statistic[i].temperature);
    }
}

/* Функция чтения файлов. Принимает путь. Возвращает адрес начала строки */
char *readFile(char *name){
    FILE *f;
    long int size = 0;
    char *ptr;

    if( (f = fopen(name, "r" )) == NULL ){
        perror("Error - ");
        return 0;
    }
    else {
        // определение размера файла
        fseek(f, 0, SEEK_END);
        size = ftell(f);

        fseek(f, 0, SEEK_SET); // возврат курсора на начало файла
        ptr = calloc(size, sizeof(char)); // выделение памяти под текущий размер файла

        fscanf(f, "%[^EOF]", ptr); // запись данных в файл
    }

    return ptr;
}

#define N 6
/* Функция конвертации полученной строки csv в массив структур dataTemp */
void temperCsv(char *csv, struct dataTemp *statistic){
    printf("--temperCsv--\n");

    long int csvlen = strlen(csv); // переменная с длиной полученной строки
    
    int tmpArr[N] = {0}; // вспомогатльный массив
    _Bool minus = 0; // переменная-флаг (1 когда число температуры отрицательное)
    int counter = 0; // счетчик количества элементов в строке
    int struct_counter = 0; // счетчик для массива структур
    int i = 0; // счетчик элементов обрабатываемой строки
    
    while(i <= csvlen){ // проверяем в цикле каждый элемент строки csv
        if(csv[i] == ';') {
            counter++;
            if(counter > N){
                counter = 0;
                minus = 0;
                printf("More parameters!");
            }
        }
        else if((csv[i] == '\n') || (csv[i] == 0)) {
            printf("line - %d\n", struct_counter);
            if(minus)
                tmpArr[counter] = 0 - tmpArr[counter];

            if(counter == 5){
                // printf("%d = %d;%d;%d;%d;%d;%d\n", counter, tmpArr[0], tmpArr[1], tmpArr[2], tmpArr[3], tmpArr[4], tmpArr[5]);
                //if(realloc(statistic, (struct_counter+1) * sizeof(statistic))){
                statistic[struct_counter].year = tmpArr[0];
                statistic[struct_counter].mounth = tmpArr[1];
                statistic[struct_counter].day = tmpArr[2];
                statistic[struct_counter].hour = tmpArr[3];
                statistic[struct_counter].minute = tmpArr[4];
                statistic[struct_counter].temperature = tmpArr[5];
                
                printf("%d-%02d-%d  %02d:%02d  t=%d\n", 
                    statistic[struct_counter].year,
                    statistic[struct_counter].mounth,
                    statistic[struct_counter].day,
                    statistic[struct_counter].hour,
                    statistic[struct_counter].minute,
                    statistic[struct_counter].temperature);

                struct_counter++; 
                // }
                // else printf("!\n");
            }
            else {
                printf("ERROR line = %d (%d;%d;%d;%d;%d;%d)\n", struct_counter+1, tmpArr[0], tmpArr[1], tmpArr[2], tmpArr[3], tmpArr[4], tmpArr[5]);
            }
            counter = 0;
            minus = 0;
            tmpArr[0]=tmpArr[1]=tmpArr[2]=tmpArr[3]=tmpArr[4]=tmpArr[5] = 0;
        }
        else if((counter == 5) && (csv[i] == '-'))
            minus = 1;
        else if(csv[i] >= '0' && csv[i] <= '9'){
            tmpArr[counter] = (tmpArr[counter] * 10) + csv[i] - '0';
        }
        else if(csv[i] != 0xD){
            counter = 0;
            minus = 0;
        }

        i++;
    }

    printf("End convert\n");
}

void doit(char *file){
    char *csv = readFile(file);

    /*****************************/
    // нахождение количества строк csv
    long int csvlen = strlen(csv);
    long int line = 0;
    int i = 0;
    while(i < csvlen){
        if((csv[i] == '\n') || (csv[i] == 0) ) // поиск по переводу строки
            line++;
        i++;
    }
    printf("line - %d\n", line);
    /*****************************/
    
    struct dataTemp *statistic; // размер массива структур = количество строк в файле

    statistic = malloc(line * sizeof(*statistic));

    temperCsv(csv, statistic);
    
    // printf("%d\n",statistic[1].temperature);
    // printf("length - %d\n",  sizeof(*statistic) / sizeof(statistic[0]));
}


int main(int argc, char **argv){
    int rez = 0;

    while((rez = getopt(argc, argv,"hf:m::")) != -1 ){
        switch (rez)
        {
        case 'h': printf("found argument \"a\" \n"); break;
        case 'f': printf("found argument \"b = %s\" \n", optarg); doit(optarg); break;
        case 'm': printf("found argument \"C = %s\" \n", optarg); break;
        case '?': printf("No param \n"); break;
        default:
            break;
        }
    }

    return 0;
}