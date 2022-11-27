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

// Cross-product
double cross(const vec &a, const vec &b) {
    return a.x * b.y - a.y * b.x;
}
double cross(const point& o, const point& a, const point& b)    {
    return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

// returns the area, which is half the determinant
double area(const vector<point> &P) {
    double result = 0.0, x1, y1, x2, y2;
    for (int i = 0; i < (int)P.size()-1; i++) {
        x1 = P[i].x; x2 = P[i+1].x;
        y1 = P[i].y; y2 = P[i+1].y;
        result += (x1 * y2 - x2 * y1);
    }
    return result / 2.0;
}

void puntosCorte(double d, const point& p, const point& q, point& cp, point& cq) {
    double x = p.y - q.y, y = q.x - p.x, t = d / dist(p, q);
    cp.x = p.x + x*t; 
    cp.y = p.y + y*t;
    cq.x = q.x + x*t; 
    cq.y = q.y + y*t;
}

point puntoInterseccion(const point& p1, const point& p2, const point& q1, const point& q2)  {
    double hq1 = cross(p1, p2, q1), hq2 = cross(p2, p1, q2);
    double hq = hq1 + hq2;
    return point((q1.x*hq2 + q2.x*hq1)/hq, (q1.y*hq2 + q2.y*hq1)/hq);
}


void printPolygon(const vector<point>& P) {
    int n = (int)P.size();
    cout.precision(3);
    for(int i=0; i<n; i++)
        cout << fixed << "(" << P[i].x << ", " << P[i].y << ") ";
    cout << endl;
    // printf("(%.3lf, %.3lf)%c", P[i].x, P[i].y, ((i < n-1) ? ' ' : '\n'));
}

int main()  {
    ios_base::sync_with_stdio(false);
    while(1)    {
        double d;
        long double aux_x, aux_y;
        int n;
        cin >> d >> n;
        // Caso nulo
        if(d == 0.0 && n == 0)
            break;
        // Guardamos al reves los puntos
        vector<point> points(n);
        for(int i=n-1; i>=0; i--)   {
            cin >> aux_x >> aux_y;
            points[i].x = aux_x;
            points[i].y = aux_y;
        }
        vector<point> cpoints(2*n);
        for(int i=0; i<n; i++)
            puntosCorte(d, points[i], points[(i+1)%n], cpoints[2*i], cpoints[2*i + 1]);
        printPolygon(cpoints);
        for(int i=0; i<n; i++)
            points[i] = puntoInterseccion(cpoints[2*i], cpoints[2*i + 1], cpoints[(2*i + 2)%(2*n)], cpoints[(2*i + 3)%(2*n)]);
        printPolygon(points);
        cout.precision(3);
        cout << fixed << area(points) << endl;
        //printf("%.3lf\n", polygon_area(n, points));
    }
    return 0;
}
