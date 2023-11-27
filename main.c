#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// gcc main.c -o main
// ./main -f data/temperature_small.csv 

struct dataTemp
{
    int year;
    int mounth;
    int day;
    int hour;
    int minute;
    int temperature;
};

/**/
char *readCsvFile(char *name){
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
        // printf("Size file \t- %ld \n", size);

        fseek(f, 0, SEEK_SET); // возврат курсора на начало файла
        ptr = calloc(size, sizeof(char)); // выделение памяти под текущий размер файла

        int Y,M,D,Hour,Min,temp;
        int r;
        while((r = fscanf(f,"%d;%d;%d;%d;%d;%d",&Y,&M,&D,&Hour,&Min,&temp)) != '\n'){
            printf("%d = %d;%d;%d;%d;%d;%d\n", r,Y,M,D,Hour,Min,temp);
    }

        fclose(f);
    }

    return ptr;
}

/*  */
void temperCsv(char *csv){
    printf("--temperCsv--\n");
    // printf("%s \n", csv);
    int i = 0;

    int tmp = 0;

    printf("%ld \n", strlen(csv));

    while(i < strlen(csv)){
        printf("%c",csv[i]);
        i++;
    }

    printf("\n");
}

void doit(char *file){
    char *scv = readCsvFile(file);
    // temperCsv(scv);
}


int main(int argc, char **argv){
    int rez = 0;

    while((rez = getopt(argc, argv,"hf:m::")) != -1 ){
        switch (rez)
        {
        case 'h': printf("found argument \"a\" \n"); break;
        case 'f': printf("found argument \"b = %s\" \n", optarg); doit(optarg); break;
        case 'm': printf("found argument \"C = %s\" \n", optarg); break;
        case '?': printf("Error! \n"); break;
        default:
            break;
        }
    }

    return 0;
}