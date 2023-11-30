#include "temp_functions.h"

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
struct dataTemp *temperCsv(char *csv){
    printf("--temperCsv--\n");

    /*****************************/
    // нахождение количества строк csv
    settings.csvLen = strlen(csv);
    if(settings.csvLen == 0){
        printf("Error. No data\n");
        exit(0);
    }

    settings.numberLine = 0;
    int i = 0;
    while(i < settings.csvLen){
        if((csv[i] == '\n') || (csv[i] == 0) ) // поиск по переводу строки
            settings.numberLine++;
        i++;
    }
    printf("line - %d\n", settings.numberLine);
    /*****************************/

    typedef struct {
        int i;
    } test;

    test **t = (test **)malloc(20 * sizeof(test *));
    for (i = 0; i < 20; ++i)
        t[i] = (test *)malloc(20 * sizeof(test));
    
    // struct dataTemp **year = malloc(12 * sizeof(year *));
    // for (i = 0; i < 31; ++i)
    //     year[i] = malloc(31 * sizeof(year));
    

    struct dataTemp *statistic; // размер массива структур = количество строк в файле
    statistic = malloc(1 * sizeof(*statistic));

    /*****************************/
    
    int tmpArr[N] = {0}; // вспомогатльный массив
    _Bool minus = 0; // переменная-флаг (1 когда число температуры отрицательное)
    int counter = 0; // счетчик количества элементов в строке
    int struct_counter = 0; // счетчик для массива структур
    i = 0; // счетчик элементов обрабатываемой строки
    
    while(i <= settings.csvLen){ // проверяем в цикле каждый элемент строки csv
        if(csv[i] == ';') {
            // printf("sym - %d counter - %d\n", csv[i], counter);
            counter++;
            if(counter > N){
                counter = 0;
                minus = 0;
                printf("More parameters!\n");
            }
        }
        else if((csv[i] == '\n') || (csv[i] == 0)) {
            // printf("line - %d\n", struct_counter);
            if(minus)
                tmpArr[counter] = 0 - tmpArr[counter];

            if(counter == 5){
                if(realloc(statistic, (struct_counter+1) * sizeof(*statistic))){
                    statistic[struct_counter].year = tmpArr[0];
                    statistic[struct_counter].mounth = tmpArr[1];
                    statistic[struct_counter].day = tmpArr[2];
                    statistic[struct_counter].hour = tmpArr[3];
                    statistic[struct_counter].minute = tmpArr[4];
                    statistic[struct_counter].temperature = tmpArr[5];
                    
                    printTempStruct(statistic, struct_counter, struct_counter);

                    struct_counter++; 
                }
                else 
                    printf("!\n");
            }
            else {
                printf("ERROR line = %d (%d;%d;%d;%d;%d;%d)\n", struct_counter+1, tmpArr[0], tmpArr[1], tmpArr[2], tmpArr[3], tmpArr[4], tmpArr[5]);
            }
            counter = 0;
            minus = 0;
            tmpArr[0]=tmpArr[1]=tmpArr[2]=tmpArr[3]=tmpArr[4]=tmpArr[5]=0;
        }
        else if((counter == 5) && (csv[i] == '-'))
            minus = 1;
        else if(csv[i] >= '0' && csv[i] <= '9'){
            tmpArr[counter] = (tmpArr[counter] * 10) + (csv[i] - '0');
        }
        else if(csv[i] == ' ') {
            i++;
            continue;
        }
        else if(csv[i] != 0xD){
            counter = 0;
            minus = 0;
        }

        i++;
    }

    printf("End convert\n");

    return statistic;
}

/* Функция вывода массива структур dataTemp с длиной line */
void printTempStruct(struct dataTemp *statistic, int start, int end){
    for(int i = start; i <= end; i++){
        printf("%d-%02d-%d  %02d:%02d  t=%d\n", 
            statistic[i].year,
            statistic[i].mounth,
            statistic[i].day,
            statistic[i].hour,
            statistic[i].minute,
            statistic[i].temperature);
    }
};