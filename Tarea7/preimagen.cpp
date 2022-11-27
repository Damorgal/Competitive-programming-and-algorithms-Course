#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int main()  {
    long long int f;
    cin >> f;
    int ans = (f%9 == 0) ? 2 : 1;
    cout << ans;
    return 0;
}
