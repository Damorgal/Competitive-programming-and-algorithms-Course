#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class bigNumber   {
private:
    int num[10000];
    int tam;
    bool signo; // 0 positivo, 1 negativo
public:
    bigNumber operator=(char *c);
    bigNumber operator+(bigNumber &BN);
    bigNumber operator*(bigNumber &BN);
    void printValue() {
        if(signo)
            printf("-");
        for(int i=0; i<tam; i++)
            printf("%d",num[i]);
        printf("\n");
    }
};

bigNumber bigNumber::operator=(char *c) {
    tam = strlen(c);
    char aux[1];
    if(c[0] != '-') {
        for(int i=0; i<tam; i++)    {
            aux[0] = c[i];
            num[i] = atoi(aux);
        }
        signo = 0;
    }
    else    {
        for(int i=1; i<tam; i++)    {
            aux[0] = c[i];
            num[i] = atoi(aux);
        }
        signo = 1;
        tam--;
    }
}

bigNumber bigNumber::operator+(bigNumber &BN) {
    bigNumber A;
    // Volteamos los numeros
    int a[10000], b[10000];
    int n = max(tam, BN.tam);
    for(int i=0; i<n; i++)  {
        if(tam <= i)
            b[i] = BN.num[BN.tam-1-i];
        else if(BN.tam <= i)
            a[i] = num[tam-1-i];
        else    {
            a[i] = num[tam-1-i];
            b[i] = BN.num[BN.tam-1-i];
        }
    }
    // Si solo es suma
    if(signo == BN.signo)   {
        int sumaPend = 0;
        for(int i=0; i<n; i++)  {
            int aux;
            if(tam <= i)
                aux = b[i] + sumaPend;
            else if(BN.tam <= i)
                aux = a[i] + sumaPend;
            else
                aux = a[i] + b[i] + sumaPend;
            if(aux/10 < 1)  {
                A.num[i] = aux;
                sumaPend = 0;
            }
            else    {
                A.num[i] = aux%10;
                sumaPend = 1;
            }
            A.tam++;
        }
        if(sumaPend)    {
            A.num[tam] = sumaPend;
            A.tam++;
        }
        if(signo)
            A.signo = 1;
        else
            A.signo = 0;
    }
    // Si es una resta
    else    {
        // Ver cual es mas grande absolutamente
        bool change;
        if(BN.tam < tam)
            change = 0;
        else if(BN.tam > tam)
            change = 1;
        else    {
            for(int i=0; i<tam; i++)    {
                if(num[i] > BN.num[i])  {
                    change = 0;
                    break;
                }
                else if(BN.num[i] > num[i]) {
                    change = 1;
                    break;
                }
            }
        }
        if(change)
            swap(a,b);
        int sumaPend = 0;
        for(int i=0; i<n; i++)  {
            int aux;
            if(tam <= i || BN.tam <= i)
                aux = a[i] - sumaPend;
            else
                aux = a[i] - b[i] - sumaPend;
            if(aux >= 0)  {
                A.num[i] = aux;
                sumaPend = 0;
            }
            else    {
                A.num[i] = aux+10;
                sumaPend = 1;
            }
            A.tam++;
        }
        if(change)  {
            if(BN.signo)
                A.signo = 1;
            else
                A.signo = 0;
        }
        else    {
            if(signo)
                A.signo = 1;
            else
                A.signo = 0;
        }
    }
    // Volteamos el numero operado
    n = A.tam/2;
    for(int i=0; i<n; i++)  {
        int aux = A.num[i];
        A.tam[i] = A.num[A.tam-1-i];
        A.num[A.tam-1-i] = aux;
    }
    return A;
}

bigNumber bigNumber::operator*(bigNumber &BN) {
    bigNumber A;
    // Volteamos los numeros
    int *a = (int*)calloc(10000,sizeof(int));
    int *b = (int*)calloc(10000,sizeof(int));
    int n = max(tam, BN.tam);
    for(int i=0; i<n; i++)  {
        if(tam <= i)
            b[i] = BN.num[BN.tam-1-i];
        else if(BN.tam <= i)
            a[i] = num[tam-1-i];
        else    {
            a[i] = num[tam-1-i];
            b[i] = BN.num[BN.tam-1-i];
        }
    }
    int sumaPend = 0, aux;
    A.tam = tam + BN.tam -1;
    for(int i=0; i<BN.tam; i++)  {
        for(int j=0; j<tam; j++)    {
            aux = sumaPend + b[i]*a[j];
            A.num[j+i] += (aux)%10;
            sumaPend = (aux)/10;
        }
        if(sumaPend)    {
            A.num[tam+i] += sumaPend;
            sumaPend = 0;
            if(i == BN.tam-1 && j==tam-1)
                A.tam++;
        }
    }
    if(signo)
        A.signo = 1;
    else
        A.signo = 0;
    free(a); free(b);
    return A;
}

int main()  {
    bigNumber A,B,C;
    A = "12233344445555566666677777778888888899999999910101010101010101010";
    B = "-12312423423";
    C = A+B;
    C.printValue();
    return 0;
}
