#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

using namespace std;

#define EPS 10e-9

struct point {
    double x, y;
    // Only used if more precision is needed
    point() { x = y = 0.0; }
    // Default constructor
    point(double _x, double _y) : x(_x), y(_y) {}
    // Copy constructor
    point(const point &p) : x(p.x), y(p.y) {}
};

bool operator == (const point &other) const {
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); }
};

// Euclidean distance
double dist(point p1, point p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

struct vec {
    double x, y;
    vec(const double &_x, const double &_y) : x(_x), y(_y) {}
};
vec toVec(const point &a, const point &b) {
    // Convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y);
}
vec scale(const vec &v, double s) {
    return vec(v.x * s, v.y * s);
}
point translate(const point &p, const vec &v) {
    // translate p according to v
    return point(p.x + v.x , p.y + v.y);
}

double dot(const vec &a, const vec &b) { return (a.x * b.x + a.y * b.y); }
double norm_sq(const vec &v) { return v.x * v.x + v.y * v.y; }

double distToLine(const point &p, const point &a, const point &b, point &c) {
    // formula: c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u)); // translate a to c
    return dist(p, c); // Euclidean distance between p and c
}

// Code from S. Halim
// Returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(const point &p, const point &a, const point &b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    // Computes the relative position of the projection of p on [ab]
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) {
        c = point(a.x, a.y); // Closer to a
        return dist(p, a);
    }
    // Euclidean distance between p and a
    if (u > 1.0) {
        c = point(b.x, b.y);
        // closer to b
        return dist(p, b);
    }
    // Euclidean distance between p and b
    return distToLine(p, a, b, c);
}

// returns the area, which is half the determinant
double area(const vector<point> &P) {
    double result = 0.0, x1, y1, x2, y2;
    for (int i = 0; i < (int)P.size()-1; i++) {
        x1 = P[i].x; x2 = P[i+1].x;
        y1 = P[i].y; y2 = P[i+1].y;
        result += (x1 * y2 - x2 * y1);
    }
    return fabs(result) / 2.0;
}

// returns true if point p is in either convex/concave polygon
bool inPolygon(const &point pt, const vector<point> &P) {
    if ((int)P.size() == 0) return false;
    double sum = 0;
    // assume the first vertex is equal to the last vertex
    for (int i = 0; i < (int)P.size()-1; i++) {
        if (ccw(pt, P[i], P[i+1]))
            sum += angle(P[i], pt, P[i+1]); // left turn/ccw
        else
            sum -= angle(P[i], pt, P[i+1]); // right turn/cw
    }
    return fabs(fabs(sum) - 2*PI) < EPS;
}

void solve(vector<point> &p1, vector<point> &p2)  {
    // Primer test
    // Como son convexos primero veamos el area para ver quien puede estar incluido en quien
    // Ponemos p1 como el poligono mas grande
    bool cambio = 0;
    if(area(p1) < area(p2)) {
        vector<point> aux = p2;
        p2 = p1;
        p1 = aux;
        cambio = 1;
    }
    // Numero de vertices de los poligonos
    int np2 = (int)p2.size();
    // Para ver si p2 esta en p1 
    // Tomamos para cada vertice de p2 vemos si está en p1 con los angulos formados
    int cont = 0;
    for(int i=0; i<np2; i++)    {
        // Esta incluido
        if(inPolygon(p2[i],p1)) 
            cont++;
    }
    if(cont == np2) {
        if(cambio)
            cout << "P1 in P2" << endl;
        else
            cout << "P2 in P1" << endl;
    }
    else if(cont > 0)
        cout << "P1 and P2 intersects" << endl;
    else
        cout << "P1 and P2 disjoint" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    vector<point> p1, p2;
    /* Lectura de los poligonos*/
    
    /* Mandar llamar funcion*/
    solve(p1,p2);
    return 0;
}
