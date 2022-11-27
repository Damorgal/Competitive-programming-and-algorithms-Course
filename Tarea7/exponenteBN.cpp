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
    void save(char *c);
    bigNumber operator+(bigNumber &BN);
    bigNumber operator*(bigNumber &BN);
    int *getArray() {return num;}
    int getTam() {return tam;}
    void printValue() {
        if(signo)
            printf("-");
        for(int i=0; i<tam; i++)
            printf("%d",num[i]);
        printf("\n");
    }
};

void bigNumber::save(char *c) {
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
            num[i-1] = atoi(aux);
        }
        signo = 1;
        tam--;
    }
}

bigNumber bigNumber::operator+(bigNumber &BN) {
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
    // Si solo es suma
    if(signo == BN.signo)   {
        int sumaPend = 0, aux;
        A.tam=0;
        for(int i=0; i<n; i++)  {
            aux = a[i] + b[i] + sumaPend;
            A.num[i] = aux%10;
            sumaPend = (int)aux/10;
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
        A.tam=0;
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
        A.num[i] = A.num[A.tam-1-i];
        A.num[A.tam-1-i] = aux;
    }
    free(a); free(b);
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
            A.num[j+i] += (aux);
            sumaPend = (int)A.num[j+i]/10;
            A.num[j+i] %= 10;
        }
        if(sumaPend)    {
            A.num[tam+i] += sumaPend;
            sumaPend = 0;
            if(i == BN.tam-1)
                A.tam++;
        }
    }
    if(signo == BN.signo)
        A.signo = 0;
    else
        A.signo = 1;
    free(a); free(b);
    // Volteamos el numero operado
    n = A.tam/2;
    for(int i=0; i<n; i++)  {
        aux = A.num[i];
        A.num[i] = A.num[A.tam-1-i];
        A.num[A.tam-1-i] = aux;
    }
    return A;
}

int main()  {
    bigNumber A,B;
    int a,b;
    char p[10000], q[10000];
    scanf("%s %s",p,q);
    //A.save("12233344445555566666677777778888888899999999910101010101010101010");
    A.save(p);
    //cout << "Numero 1: "; A.printValue();
    //B.save("12312423423");
    B.save(q);
    //cout << "Numero 2: "; B.printValue();
    int *vec = A.getArray();
    a = vec[A.getTam() -1];
    vec = B.getArray();
    b = vec[B.getTam()-2]*10 + vec[B.getTam()-1];
    switch(a)   {
        case(2):
            b = b%4;
            printf("%d\n", b==1 ? 2 :(b==2 ? 4 :(b==3 ? 8 : 6)));
            break;
        case(3):
            b = b%4;
            printf("%d\n", b==1 ? 3 :(b==2 ? 9 :(b==3 ? 7 : 1)));
            break;
        case(7):
            b = b%4;
            printf("%d\n", b==1 ? 7 :(b==2 ? 9 :(b==3 ? 3 : 1)));
            break;
        case(8):
            b = b%4;
            printf("%d\n", b==1 ? 8 :(b==2 ? 4 :(b==3 ? 2 : 6)));
            break;
        case(4):
            b = b%2;
            printf("%d\n", b==1 ? 4 : 6);
            break;
        case(9):
            b = b%2;
            printf("%d\n", b==1 ? 9 : 1);
            break;
        default:
            printf("%d\n",a);
            break;
    }
    return 0;
}
