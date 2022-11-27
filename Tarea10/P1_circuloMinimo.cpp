#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

#define EPS 1e-9

struct point {
    double x, y;
    // Only used if more precision is needed
    point() { x = y = 0.0; }
    // Default constructor
    point(double _x, double _y) : x(_x), y(_y) {}
    // Copy constructor
    point(const point &p) : x(p.x), y(p.y) {}
    // Sobrecarga
    bool operator == (const point &other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); }
    bool operator < (const point other)const{
        return x < other.x;
    }
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

double angle(const point &a, const point &o, const point &b) {
    //returns angle aob in rad (without sign)
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

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

// Cross-product
double cross(const vec &a, const vec &b) {
return a.x * b.y - a.y * b.x;
}
// Returns true if point r is on the left side of line pq
bool ccw(const point &p, const point &q, const point &r) {
return cross(toVec(p, q), toVec(p, r)) > 0;
}

// Returns true if point r is on the left side of line pq
bool ccw(const point &p, const point &q, const point &r, bool ref) {
return ref?(cross(toVec(p, q), toVec(p, r))>-EPS):(cross(toVec(p, q), toVec(p, r))<EPS);
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
    return fabs(fabs(sum) - 2*M_PI) < EPS;
}

// Regresa true si el poligono puede envolverse en un circulo de radio r
bool inCircleRadius(vector<point> P, double r)  {
    return false;
}

double welz(vector<point> P, vector<point> R)   {
    if(P.empty() || (int)R.size()==3)   {
        if((int)R.size() == 3)  {
            // Checamos si es un tringulo acutangulo
            if(angle(R[0],R[1],R[2]) <= M_PI/2+EPS &&
               angle(R[1],R[2],R[0]) <= M_PI/2+EPS &&
               angle(R[2],R[0],R[1]) <= M_PI/2+EPS) 
                // Ley de senos
                return (double)dist(R[0],R[2])/(2*sin(angle(R[0],R[1],R[2])));
            else    {
                // Regresamos la distancia maxima
                double m = dist(R[0],R[1]);
                if(m < dist(R[0],R[2])) m = dist(R[0],R[2]);
                if(m < dist(R[1],R[2])) m = dist(R[1],R[2]);
                return m;
            }
        }
        return 0.0;
    }
    // Seleccionamos random un punto
    int ip = (int)(rand()*1e9) % (int)P.size();
    vector<point> aux_P = P;
    aux_P[ip] = aux_P.back();
    aux_P.pop_back();
    double radio = welz(aux_P, R);
    if(inCircleRadius(P, radio))
        return radio;
    R.push_back(P[ip]);
    return welz(aux_P, R);
}

// Basado en algoritmo de Welz's en wikipedia
// Al parecer era un problema muy dificil y famoso
long double solve(vector<point> P)    {
    // Primero encontramos un punto que pertenzca al círculo englobante
    // O(n^2)
    int np = (int)P.size(), i_pos, j_pos;
    double max_dist = -1;
    for(int i=0; i<np; i++)
        for(int j=i+1; j<np; j++)   {
            double aux = dist(P[i], P[j]);
            if(max_dist < aux)  {
                max_dist = aux;
                i_pos = i;
                j_pos = j;
            }
        }
    // Un punto posible puede ser i_pos o j_pos
    // Hacemos algoritmo para uno
    // O(n)
    vector<point> R;
    double ans = welz(P,R.push_back(P[i_pos]));
}


int main() {
    ios_base::sync_with_stdio(false);
    while(cin >> N) {
        if(N == -1) 
            return 0;
        // Leemos los puntos
        for(int i=1; i<=N; i++) 
            cin >> points[i].x >> points[i].y;
        sort(points + 1, points + N + 1);
        cout.precision(3);
        cout << fixed << solve(1, N) << endl;
    }
    
    
    return 0;
}
