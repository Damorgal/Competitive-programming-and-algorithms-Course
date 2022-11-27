#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;


int main()  {
    int n=30, ans=0;
    string s;
    for(int i=3; i<=n; i++) {
        s.clear();
        for(int j=0; j<i; j++)
            s.push_back('x');
        for(int j=i; j<n; j++)
            s.push_back('y');
        do {
            for(int k=0; k<n-2; k++)    {
                if(s[k] == 'x' && s[k+1] == 'x' && s[k+2] == 'x')   {
                    ans++;
                    break;
                }
            }
        } while(next_permutation(s.begin(), s.end()));
    }
    cout << "La respuesta para n="<<n<<" es: " << ans <<endl;
    return 0;
}
