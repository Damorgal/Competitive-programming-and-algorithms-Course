#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <string>

using namespace std;



int main(int argv, const char * argc[]) {
    string p;
    int con = 1;

    getline(cin,p);
    while (p != "end") {
        vector< stack<char> > containers;
        stack<char> s;
        s.push(p[0]);
        containers.push_back(s);
        s.pop();
        for (int i=1; i<p.length(); i++) {
            int j;
            for(j=0; j<containers.size(); j++){

                if (p[i] <= containers[j].top()) {
                    containers[j].push(p[i]);
                    break;
                }
            }
            // Si no se pudo agregar a ninguna pila
            if(j == containers.size()){
                s.push(p[i]);
                containers.push_back(s);
                s.pop();
            }
        }
        printf("Case %d: %d\n",con, (int)containers.size());
        con++;
        getline(cin,p);
    }
    return 0;
}
