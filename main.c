#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct temp
{
    int year;
    int mounth;
    int day;
    int hour;
    int minute;
    int temperature;
};

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
        // printf("Size file \t- %ld \n", size);

        fseek(f, 0, SEEK_SET); // возврат курсора на начало файла
        ptr = calloc(size, sizeof(char)); // выделение памяти под текущий размер файла
        fscanf(f, "%[^EOF]", ptr); // считывание файла в выделенную память
        // printf("Size ptr \t- %d \n", strlen(ptr));

        fclose(f);
    }

    return ptr;
}

void temperCsv(char *csv){
    printf("--temperCsv--\n");
    // printf("%s \n", csv);
    int i = 0;
    while(i < strlen(csv)){
        while(csv[i] != '\n'){
            printf("%c",csv[i]);
            i++;
        }
        printf("\n--\n");
        i++;
    }
    
}


int main(int argc, char **argv){

    char *scv = readFile(".\\data\\temperature_small.csv");
    temperCsv(scv);
    
    int rez = 0;

    while((rez = getopt(argc, argv,"hf:m::")) != -1 ){
        switch (rez)
        {
        case 'h': printf("found argument \"a\" \n"); break;
        case 'f': printf("found argument \"b = %s\" \n", optarg); break;
        case 'm': printf("found argument \"C = %s\" \n", optarg); break;
        case '?': printf("Error! \n"); break;
        default:
            break;
        }
    }

    return 0;
}