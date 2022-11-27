#include <cstdio>
#include <algorithm>

using namespace std;

int N, M;
char g[25][25];
int dp[25][25][25][25];
bool vec[25][25][25][25];

int ganador(int a, int b, int c, int d){
	if (a >= c || b >= d) 
        return 0;
	if (vec[a][b][c][d]) 
        return dp[a][b][c][d];
	vec[a][b][c][d] = true;
	bool ans[410] = {false};
	for (int i = a; i < c; i++)	{
		for (int j = b; j < d; j++){
			int x;
			// Hacemos el XOR
			if (g[i][j] == '-') {
				x = ganador(a, b, i, d) ^ ganador(i+1, b, c, d);
			} else if (g[i][j] == '|') {
				x = ganador(a, b, c, j) ^ ganador(a, j+1, c, d);
			} else {
				x = ganador(a, b, i, j) ^ ganador(i+1, b, c, j) ^ ganador(a, j+1, i, d) ^ ganador(i+1, j+1, c, d);
			}
			ans[x] = true;
		}
	}
	int ind = 0;
    while(ans[ind++]); 
    ind--;
    dp[a][b][c][d] = ind;
    return ind;
}

int main(){
	// Leemos datos del tablero
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%s", g[i]);
    int ans = ganador(0,0,N,M);
    ans != 0 ? printf("WIN\n") : printf("LOSE\n");
}
