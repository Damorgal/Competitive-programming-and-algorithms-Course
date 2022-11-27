#include <iostream>
#include <stdio.h>
#include <cstdlib>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    //Sobrecargamos
    unsigned long long sobrecarga[27];
    sobrecarga[0]=sobrecarga[1]=sobrecarga[2]=0;
    sobrecarga[3]=1; sobrecarga[4]=6; sobrecarga[5]=31;
    sobrecarga[6]=155; sobrecarga[7]=771; sobrecarga[8]=3850;
    sobrecarga[9]=19363; sobrecarga[10]=98187; sobrecarga[11]=502063;
    sobrecarga[12]=2587937; sobrecarga[13]=13440857; sobrecarga[14]=70296473;
    sobrecarga[15]=370019079; sobrecarga[16]=1959106674; sobrecarga[17]=10428220683;
    sobrecarga[18]=55779368219; sobrecarga[19]=299681788263; sobrecarga[20]=1616594895397;
    sobrecarga[21]=8752745540025; sobrecarga[22]=47550361333961; sobrecarga[23]=259124455145823;
    sobrecarga[24]=1416118615851221; sobrecarga[25]=7759443920290221; sobrecarga[26]=42620109348084205;
    int n;
    while(cin>>n)
        printf("%lld\n",sobrecarga[n]);
    return 0;
}
