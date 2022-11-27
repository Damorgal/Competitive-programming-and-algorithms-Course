#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define EPS 1e-9
int N;

struct point    {
    double x, y;
    // Only used if more precision is needed
    point() {x = y = 0.0;}
    // Default constructor
    point(double _x, double _y) : x(_x), y(_y)  {}
    // Copy constructor
    point(const point &p) : x(p.x), y(p.y)  {}
    // Sobrecarga
    bool operator == (const point &other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));  }
    // Ordenamos los puntos por coordenada x
    bool operator < (const point &other) const  {
        return (x < other.x);  }
};

// Euclidean distance
long double dist(point p1, point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

long double solve(vector<point> &points, int low, int high)    {
    if(high-low < 2) 
        return 1.e15;
    // Si ya solo son 3 puntos
    if(high-low == 2) 
        return dist(points[low], points[low + 1]) + 
               dist(points[low+1], points[high]) + 
               dist(points[low], points[high]);
    long double ans = 1.e15;
    int middle = (low+high) >> 1;
    ans = min(ans, solve(points, low, middle));
    ans = min(ans, solve(points, middle+1, high));
    vector<point> closest;
    for(int i=low; i<=high; i++)
        if(fabs(points[i].x-points[middle].x) <= ans/2.0)
            closest.push_back(points[i]);
    int tam = (int)closest.size();
    for(int i=0; i<tam; i++)
        for(int j=i+1; j<tam; j++)
            for(int k=j+1; k<tam; k++)
                ans = min(ans,
                             dist(closest[i], closest[j]) +
                             dist(closest[j], closest[k]) +
                             dist(closest[i], closest[k]));
    return ans;
}


int main() {
    ios_base::sync_with_stdio(false);
    vector<point> points;
    double aux_x, aux_y;
    while(cin >> N) {
        if(N == -1) 
            return 0;
        // Leemos los puntos
        points.push_back(point());
        for(int i=1; i<=N; i++) {
            cin >> aux_x >> aux_y;
            points.push_back(point(aux_x, aux_y));
        }
        // Ordenamos los puntos por coordenada x
        sort(points.begin() + 1, points.end());
        cout.precision(3);
        cout << fixed << solve(points, 1, N) << endl;
        points.clear();
    }
    
    
    return 0;
}
