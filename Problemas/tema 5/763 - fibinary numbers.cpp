#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>

#define tam 150

char *a,*b;
int *ans;

void algoritmo()    {
    int i,j,k;
    ans = (int*)calloc(tam,sizeof(int));
    k=strlen(a)-1;
    for(i=k,j=0; i>=0; i--,j++)
        ans[j] += a[i]-'0';
    k=strlen(b)-1;
    for(i=k,j=0; i>=0; i--,j++)
        ans[j] += b[i]-'0';
    while(1)    {
        for(i=0; i<110; i++)  {
            if(ans[i] && ans[i+1])   {
                ans[i]--;
                ans[i+1]--;
                ans[i+2]++;
                break;
            }
            else if(ans[i]>1)    {
                ans[i] -= 2;
                if(i==0)
                    ans[i+1]++;
                else if(i==1)    {
                    ans[i+1]++;
                    ans[i-1]++;
                }
                else    {
                    ans[i+1]++;
                    ans[i-2]++;
                }
                break;
            }
        }
        if(i==110)
            break;
    }
    for(i=110; i>0; i--)
        if(ans[i])
            break;
    for (; i>=0; i--)
        printf("%d",ans[i]);
    printf("\n");
    free(ans);
}

int main()  {
    int t=0;
    a = (char*)malloc(tam*sizeof(char));
    b = (char*)malloc(tam*sizeof(char));
    while(scanf("%s%s",a,b)==2) {
        if(t++)
            printf("\n");
        algoritmo();
    }
    free(a);
    free(b);
    return 0;
}
