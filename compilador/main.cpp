#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main() {
    int t;
    scanf("%d",&t);
    int caso=1;
    while(t--)    {
        char *num = (char*)malloc(1100*sizeof(char));
        scanf("%s",num);
        int *cantidad = (int*)calloc(15,sizeof(int));
        int sum=0;
        for(int i=0; num[i]; i++)   {
            sum += num[i]-'0';
            cantidad[num[i]-'0']++;
        }
        int permitido=cantidad[3]+cantidad[6]+cantidad[9];
        int s=1;
        if(sum%3 == 0)  {
            if(permitido%2 == 0)
                s=0;
        }
        else if(sum%3 == 1) {
            if(cantidad[1] || cantidad[4] || cantidad[7]) {
                if(permitido % 2)
                    s=0;
            }
            else
                s=0;
        }
        else    {
            if(cantidad[2] || cantidad[5] || cantidad[8])   {
                if(permitido % 2)
                    s=0;
            }
            else
                s=0;
        }
        printf("Case %d: ",caso++);
        if(s)
            printf("S\n");
        else
            printf("T\n");
        free(cantidad);
        free(num);
    }
    return 0;
}
