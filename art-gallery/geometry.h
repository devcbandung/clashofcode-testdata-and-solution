#pragma once

#include <bits/stdc++.h>
using namespace std;

double _acos(double x) {
	double ret = acos(x);
	if (ret == ret) return ret;
	if (x < 0) return acos(-1.0);
	return acos(1.0);
}
#define acos _acos
#define sqr(x) ((x)*(x))

const double PI = acos(-1);
const double EPS = 1e-7;
const double INF = 1e300;

bool cmpf(const double a, const double b) {
	return fabs(a - b) < EPS;
}

struct point{
	double x, y;
	point() { x = y = 0; }
	point(double x, double y) : x(x), y(y) {}
	point(pair<double,double> p) : x(p.first), y(p.second) {}
	point(pair<int,int> p) : x(p.first), y(p.second) {}
	point(pair<long long,long long> p) : x(p.first), y(p.second) {}
};
struct segment {
	point p1, p2;
	segment() {p1 = p2 = point(0,0);}
	segment(point p1, point p2) : p1(p1), p2(p2) {}
};

/** basic operators and functions of point and segment **/
/* complexity: constant */
point operator-(const point &p1, const point &p2) {
	return point(p1.x - p2.x, p1.y - p2.y);
}
point operator+(const point &p1, const point &p2) {
	return point(p1.x + p2.x, p1.y + p2.y);
}
point operator*(const point &p, const double &s) {
	return point(p.x * s, p.y * s);
}
point operator/(const point &p, const double &s) {
	return p * (1./s);
}
bool operator<(const point &p1, const point &p2) {
	if (p1.x != p2.x) return p1.x < p2.x;
	return p1.y < p2.y;
}
bool operator==(const point &p1, const point &p2) {
	return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS;
}
double cross(const point &p1, const point &p2) {
	/* returns z-component of cross product of two points (vectors) */
	return p1.x * p2.y - p1.y * p2.x;
}
double dot(const point &p1, const point &p2) {
	/* returns dot product of two points (vectors) */
	return p1.x * p2.x + p1.y * p2.y;
}
double dist(const point &p){
	/* returns distance of p from the origin */
	return sqrt(sqr(p.x) + sqr(p.y));
}
double dist(const point &p1, const point &p2) {
	/* returns distance between two points */
	return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
double length(const segment &s) {
	/* returns length of a segment */
	return sqrt(sqr(s.p1.x - s.p2.x) + sqr(s.p1.y - s.p2.y));
}
double getAngle(const point &p1, const point &p2) {
	/* returns angle formed by two vectors. WARNING: undirected angle */
	return fabs(acos(dot(p1,p2) / dist(p1,point(0,0)) / dist(p2,point(0,0))));
}
double getAngle(const point &p1, const point &center, const point &p2) {
	/* returns angle formed by three points. WARNING: undirected angle */
	return getAngle(p1 - center, p2 - center);
}
double distToSegment(const point &p, const segment &s) {
	/* returns distance of a point to a segment */
	if (getAngle(s.p2, s.p1, p) > PI/2 + EPS || getAngle(s.p1, s.p2, p) > PI/2 + EPS) return min(dist(p,s.p1), dist(p,s.p2));
	return fabs(cross(s.p1 - p, s.p2 - p)) / dist(s.p1, s.p2);
}
double distToLine(const point &p, const segment &s){
	/* returns distance of a point to a line (its orthogonal projection) */
	return fabs(cross(s.p1 - p, s.p2 - p)) / dist(s.p1, s.p2);
}
point rotate(const point &p, const double &alpha) {
	/* rotates a point with respect to the origin. alpha in radians */
	return point(p.x * cos(alpha) - p.y * sin(alpha), p.x * sin(alpha) + p.y * cos(alpha));
}
point rotate(const point &p, const point &center, const double &alpha){
	/* rotates a point with respect to point center. alpha in radians */
	return center + rotate(p - center, alpha);
}
point rescale(const point &p, const double s) {
	return point(p.x * s, p.y * s);
}
point dilate(const point &p, const double Factor){
	return rescale(p, Factor);
}
point dilate(const point &p, const point &center, double factor){
	return dilate(p- center, factor) + center;
}
bool isRightTurn(const point &p1, const point &p2, const point &p3){
	return cross(p2 - p1, p3 - p2) < EPS;
	/* straight returns true */
}
bool isStraight(const point &p1, const point &p2, const point &p3){
	double c = cross(p2 - p1, p3 - p2);
	return cmpf(c, 0);
}
bool isOnSameSide(const point &p1, const point &p2, const segment &s){
	double z1 = cross(s.p2 - s.p1, p1 - s.p1);
	double z2 = cross(s.p2 - s.p1, p2 - s.p1);
	return (z1 + EPS < 0 && z2 + EPS < 0) || (0 < z1 - EPS && 0 < z2 - EPS) || fabs(z1) < EPS || fabs(z2) < EPS;
	/* on segment returns true */
}
bool isOnLine(const point &p, const segment &l){
	return fabs((l.p1.y - p.y) * (l.p2.x - p.x) - (l.p2.y - p.y) * (l.p1.x - p.x)) < EPS;
}
bool isOnSegment(const point &p, const segment &s){
	double c = cross(p - s.p1, s.p2 - p);
	if (fabs(c) > EPS) return false;
	double d = dot(s.p2 - s.p1, p - s.p1);
	return d > -EPS && d < sqr(s.p2.x - s.p1.x) + sqr(s.p2.y - s.p1.y) + EPS;
}
bool isIntersecting(const segment &s1, const segment &s2){
	return !(isOnSameSide(s1.p1,s1.p2,s2) || isOnSameSide(s2.p1,s2.p2,s1)) || isOnSegment(s1.p1,s2) || isOnSegment(s1.p2,s2) || isOnSegment(s2.p1,s1) || isOnSegment(s2.p2,s1);
}
bool isParallel(const segment &s1, const segment &s2){
	return fabs((s1.p1.y-s1.p2.y)*(s2.p1.x-s2.p2.x)-(s2.p1.y-s2.p2.y)*(s1.p1.x-s1.p2.x)) < EPS;
}
point intersection(const segment &s1, const segment &s2){
	/* assumes !isParallel(s1,s2) */
	double x1 = s1.p1.x - s1.p2.x;
	double x2 = s2.p1.x - s2.p2.x;
	double y1 = s1.p1.y - s1.p2.y;
	double y2 = s2.p1.y - s2.p2.y;
	double cross1 = cross(s1.p1, s1.p2);
	double cross2 = cross(s2.p1, s2.p2);
	return point ((cross1 * x2 - cross2 * x1) / (x1 * y2 - x2 * y1), (cross1 * y2 - cross2 * y1) / (x1 * y2 - x2 * y1));
}
point projection(const point &p, const segment &s){
	/* projects p onto line s */
	return rescale(s.p2 - s.p1, dot(p - s.p1, s.p2 - s.p1) / sqr(length(s))) + s.p1;
}
point reflection(const point &p, const point &center){
	/* reflect p with respect to center */
	return center * 2. - p;
}
point reflection(const point &p, const segment &s){
	/* reflect p with respect to line s */
	return reflection(p, projection(p, s));
}
segment lineBisector(const point &p1, const point &p2){
	point center = (p1 + p2) / 2.;
	return segment(rotate(p1,center,PI/2.), rotate(p2,center,PI/2.));
}
segment lineBisector(const segment &s){
	return lineBisector(s.p1, s.p2);
}

/** introducing polygon **/
typedef vector<point> polygon;

/** Area of Polygon **/
/* complexity : O(N) */
double polygonArea(polygon p){
	double area = p.front().y * p.back().x - p.front().x * p.back().y;
	for (int i = 0; i + 1 < (int)p.size(); ++i){
		area += p[i].x * p[i+1].y;
		area -= p[i].y * p[i+1].x;
	}
	return fabs(area) / 2.;
}

/** Check orientation of points: clockwise or counterclockwise **/
/* complexity : O(N) */
bool isClockwise(polygon p){
	double area = p.front().y * p.back().x - p.front().x * p.back().y;
	for (int i = 0; i + 1 < (int)p.size(); ++i){
		area += p[i].x * p[i+1].y;
		area -= p[i].y * p[i+1].x;
	}
	return area < 0;
}

/** Check position of a point with respect to a polygon  **/
/* complexity : O(N) */
bool isPointInsidePolygon(point p, const polygon &poly){
	/* ray casting to the right */
	segment ray (p,p+point(1,0));
	int n = (int)poly.size();
	/* counts the number of intersections */
	int nIntersection = 0;
	for (int i = 0; i < n; ++i){
		segment side(poly[i],poly[(i+1)%n]);
		if (isOnSegment(p,side)) {
			return false;
		}
		if (isParallel(ray,side)) continue;
		point x = intersection(ray,side);
		if (isOnSegment(x,side) && dot(x-p,ray.p2-p) > -EPS){
			/* special case: x is one of vertices of sides */
			if (x == side.p1){
				if (isRightTurn(p,x,side.p2)) nIntersection ++;
			}
			else if (x == side.p2){
				if (isRightTurn(p,x,side.p1)) nIntersection ++;
			}
			else nIntersection ++;
		}
	}
	return nIntersection % 2 == 1;
}

/** Convex Hull | monotone chain algorithm **/
/* complexity : O(N log N) */
polygon convexHull(polygon p){
	int m = 0, n = p.size();
	polygon hull(2*n);
	sort(p.begin(),p.end());
	for (int i = 0; i < n; ++i){
		while (m >= 2 && isRightTurn(hull[m-2],hull[m-1],p[i]) && !isStraight(hull[m-2],hull[m-1],p[i])) --m;
		hull[m++] = p[i];
	}
	for (int i = n-1, t = m+1; i >= 0; --i){
		while (m >= t && isRightTurn(hull[m-2],hull[m-1],p[i]) && !isStraight(hull[m-2],hull[m-1],p[i])) --m;
		hull[m++] = p[i];
	}
	hull.resize(m);
	// remove any two consecutive points
	for (int i = 0; hull.size() > 1 && i < hull.size(); ++i) {
		if (hull[i] == hull[(i+1)%hull.size()]) {
			hull.erase(hull.begin()+i);
			i--;
		}
	}
	return hull;
}
