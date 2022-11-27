#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int fiboNumbers[10000];


class fibinary   {
private:
    int num[10000];
    int tam;
public:
    fibinary save(char *c);
    fibinary operator+(fibinary &f);
    void printValue() {
        for(int i=0; i<tam; i++)
            printf("%d",num[i]);
        printf(" = ");
        int suma=0;
        for(int i=0; i<tam; i++)
            suma += fiboNumbers[i+1]*num[tam-1-i];
        printf("%d\n",suma);
    }
};

fibinary fibinary::save(char *c) {
    tam = strlen(c);
    char aux[1];
    for(int i=0; i<tam; i++)    {
        aux[0] = c[i];
        num[i] = atoi(aux);
    }
}

fibinary fibinary::operator+(fibinary &f) {
    // Volteamos los numeros
    int *a = (int*)calloc(10000,sizeof(int));
    int *b = (int*)calloc(10000,sizeof(int));
    int n = max(tam, f.tam);
    for(int i=0; i<n; i++)  {
        if(tam <= i)
            b[i] = f.num[f.tam-1-i];
        else if(f.tam <= i)
            a[i] = num[tam-1-i];
        else    {
            a[i] = num[tam-1-i];
            b[i] = f.num[f.tam-1-i];
        }
    }
    fibinary ans;
    for(int i=0; i<n; i++)  {
        if(a[i] != b[i])
            ans.num[i] += 1;
        else if(a[i] == 0)
            ans.num[i] += 0;
        else if(i>=2)   {
            ans.num[i+1]++;
            ans.num[i-2]++;
        }
        else    {
            if(i==0)
                ans.num[1]++;
            else    {
                ans.num[0]++;
                ans.num[2]++;
            }
        }
    }
    // Acarreamos
    bool flag=0;
    while(1){
        if(ans.num[tam] != 0 || ans.num[tam-1] >1)
            ans.tam = tam+1;
        else
            ans.tam = tam;
        for(int i=ans.tam-1; i>1; i--) {
            if(ans.num[i]>1) {
                ans.num[i+1] += 1;
                ans.num[i-2] += 1;
                flag = 1;
                ans.num[i] -= 2;
            }
        }
        if(!flag)
            break;
    }
    // Volteamos el numero operado
    n = ans.tam/2;
    for(int i=0; i<n; i++)  {
        int aux = ans.num[i];
        ans.num[i] = ans.num[ans.tam-1-i];
        ans.num[ans.tam-1-i] = aux;
    }
    return ans;
}

int main()  {
    fiboNumbers[0] = fiboNumbers[1] = 1;
    for(int i=2; i<1000; i++)
        fiboNumbers[i] = fiboNumbers[i-1] + fiboNumbers[i-2];
    fibinary A,B,C;
    cout << "El primer valor es:"<<endl;
    A.save("10101001");
    A.printValue();
    cout<<"El segundo valor es:"<<endl;
    B.save("10010");
    B.printValue();
    cout << "La suma es: "<<endl;
    C = A+B;
    C.printValue();
    return 0;
}
