#include <stdio.h>
// #include <conio.h>
#define N 6
int main(int argc, char **argv)
{
    FILE *open;
    char name[] = ".\\data\\temperature_small.csv";
    open = fopen(name, "r");
    if(open==NULL)
        return 1;

    char ch;

    int counter = 0;
    int arr[6] = {0};

    _Bool minus = 0;

    while((ch = fgetc(open)) != EOF) {
        if(ch == ';') {
            counter++;
            if(counter > N){
                counter = 0;
                minus = 0;
            }
        }
        else if(ch == '\n') {
            if(minus)
                arr[counter] = 0 - arr[counter];

            if(counter == 5)
                printf("%d = %d;%d;%d;%d;%d;%d\n", counter, arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
            else {
                printf("ERROR %d = %d;%d;%d;%d;%d;%d\n", counter, arr[0],arr[1],arr[2],arr[3],arr[4],arr[5]);
            }

            counter = 0;
            minus = 0;
            arr[0]=arr[1]=arr[2]=arr[3]=arr[4]=arr[5]=0;
        }
        else if((counter == 5) && (ch == '-'))
            minus = 1;
        else if(ch >= '0' && ch <= '9'){
            arr[counter] = (arr[counter] * 10) + ch - '0';
        }
        else if(ch != 0xD){
            counter = 0;
            minus = 0;
        }
    }
}
