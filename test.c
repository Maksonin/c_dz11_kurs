#include <stdio.h>
// #include <conio.h>
#define N 3
int main(int argc, char **argv)
{
    FILE *open;
    char name[] = "data/temperature_small.csv";
    open = fopen(name, "r");
    if(open==NULL)
        return 1;
    int Y,M,D;
    int r;
    while((r = fscanf(open,"%d;%d;%d",&Y,&M,&D)) != EOF){
        // if(r<N) {
        //     char s[20],c;
        //     r = fscanf(open,"%[^\n]%c", s,&c);
        //     printf("ERROR %d=%s%x\n",r,s,c);
        // }
        // else
            printf("%d =%d;%d;%d\n", r,Y,M,D);
    }
    return 0;
}
