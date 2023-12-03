#include "temp_functions.h"

/* Фунция объединяющая все действия для получения статистики из файла */
void getStatistic(char *fileN, int month){
    printf("DoIT!\n");
    char *csv;
    // printf("%s\n", fileN);
    // printf("%d\n", month);

    // если имя файла присутствует
    if(fileN)
        csv = readFile(fileN); // читаем файл
    else { // если имя файла не передано в переменной
        printf("The program didn't  recieve -f parametr. Change default file (temper_data.csv)\n");
        csv = readFile(defaultFile); // читаем файл по умолчанию
    }
    if(!csv){ // если ни один файл не прочитан
        printf("Error! The CSV file is missing!\n");
        exit(1);
    }

    if(month > 0)
        month -= 1;
    
    stack *statistic = temperCsv(csv);

    free(csv); // освобождение памяти выделенной для хранения данных из файла

    printStatistic(statistic, month);
}

/* Функция выводит статистику темпаратуры по определенному месяцу или году */
void printStatistic(stack *statistic, int month){
    printf("Print statistic!\n");
    float sr_temp = 0;
    int j = 0;
    int min_temp;
    int max_temp;

    if(month > 0){
        if(statistic[month].sp == 0){
            printf("No statistic for this month\n");
            exit(0);
        }
        printf("Statistick on month - %d\n", month+1);

        for(int i = 0; i < statistic[month].size - 1; i++){
            if(i == 0){
                min_temp = statistic[month].data[i].temperature;
                max_temp = statistic[month].data[i].temperature;
            }
            printTempStruct(statistic[month].data, i, i);

            sr_temp += statistic[month].data[i].temperature;
            if(statistic[month].data[i].temperature > max_temp)
                max_temp = statistic[month].data[i].temperature;
            if(statistic[month].data[i].temperature < min_temp)
                min_temp = statistic[month].data[i].temperature;
            
            j++;
        }
    }
    else if(month == 0){
        printf("All statistick\n");
        for(int i = 0; i < 12; i++){
            for(int i1 = 0; i1 < statistic[i].size - 1; i1++){
                if(i == 0){
                    min_temp = statistic[month].data[i].temperature;
                    max_temp = statistic[month].data[i].temperature;
                }
                
                sr_temp += statistic[i].data[i1].temperature;
                if(statistic[i].data[i1].temperature > max_temp)
                    max_temp = statistic[i].data[i1].temperature;
                if(statistic[i].data[i1].temperature < min_temp)
                    min_temp = statistic[i].data[i1].temperature;
                
                j++;
            }
        }
    }
    sr_temp /= j;

    printf("Middle - %.2f \tMinimum - %d \tMaximum - %d\n", sr_temp, min_temp, max_temp);
}

#define count 6 // число параметров, которое должна считать программа в строке

/* Функция конвертации полученной строки csv в массив структур dataArr */
stack *temperCsv(char *csv){
    // нахождение количества строк csv
    csvLen = strlen(csv);
    if(csvLen == 0){ 
        printf("Error. No data\n");
        exit(1);
    }

    stack *dataArr;
    dataArr = malloc(12 * sizeof(*dataArr)); // выделяем память под 12 динамических массивов (свой для каждого месяца)

    for(int i = 0; i < 12; i++){
        init_stack(&dataArr[i]); // выделяем память для каждого из 12 массивов
    }
    
    int tmpArr[count] = {0}; // вспомогатльный массив
    dataTemp tmpStr;
    _Bool minus = 0; // переменная-флаг (1 когда число температуры отрицательное)
    int counter = 0; // счетчик количества элементов в строке
    int struct_counter = 0; // счетчик для массива структур
    int i = 0; // счетчик элементов обрабатываемой строки
    
    printf("Start convert\n");
    while(i <= csvLen){ // проверяем в цикле каждый элемент строки csv
        if(csv[i] == ';') {
            // printf("sym - %d counter - %d\n", csv[i], counter);
            counter++;
            if(counter > count){
                counter = 0;
                minus = 0;
                printf("More parameters!\n");
            }
        }
        else if((csv[i] == '\n') || (csv[i] == 0)) {
            if(counter == 5){
                    if(minus)
                        tmpArr[counter] = 0 - tmpArr[counter];

                    tmpStr.year = tmpArr[0];
                    tmpStr.month = tmpArr[1];
                    tmpStr.day = tmpArr[2];
                    tmpStr.hour = tmpArr[3];
                    tmpStr.minute = tmpArr[4];
                    tmpStr.temperature = tmpArr[5];

                    push(&dataArr[tmpArr[1] - 1], &tmpStr);

                    tmpStr.year = 0;
                    tmpStr.month = 0;
                    tmpStr.day = 0;
                    tmpStr.hour = 0;
                    tmpStr.minute = 0;
                    tmpStr.temperature = 0;

                    struct_counter++; 
            }
            else {
                printf("ERROR on line = %d (%d;%d;%d;%d;%d;%d)\n", struct_counter+1, tmpArr[0], tmpArr[1], tmpArr[2], tmpArr[3], tmpArr[4], tmpArr[5]);
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

    return dataArr;
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

/* Функция вывода массива структур dataTemp с длиной line */
void printTempStruct(dataTemp *statistic, int start, int end){
    for(int i = start; i <= end; i++){
        printf(" - %d-%02d-%d - %02d:%02d  t=%d\n",
            statistic[i].year,
            statistic[i].month,
            statistic[i].day,
            statistic[i].hour,
            statistic[i].minute,
            statistic[i].temperature);
    }
};

/* Функция  выделения памяти для динамического массива data*/
void init_stack(stack *st){
    st->size = 1;
    st->sp=0;
    st->data=malloc(1 * sizeof(dataTemp));
}

/* Фунция добавления элемента в динамический массив st */
void push (stack *st, dataTemp *value){
    if(st->sp == st->size-1)
    {
        st->size = st->size+1;
        st->data = realloc(st->data, st->size * sizeof(dataTemp));
    }
    st->data[st->sp++] = *value;
}