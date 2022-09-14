#include <iostream>
using namespace std;

//struct that represents a point
struct Point
{
	float x;
	float y;
};

//this function checks if the point is in circle
bool isInCircle(Point p) {
	Point c;
	float r;
	cout << "Enter the x coordinate of the center: ";
	cin >> c.x;
	cout << "Enter the y coordinate of the center: ";
	cin >> c.y;
	cout << "Enter the radius: ";
	cin >> r;
	if(r<0) r=abs(r); //making sure that the radius will always be positive number 

	float deltha_x = p.x - c.x;
	float deltha_y = p.y - c.y;
	float result = deltha_x * deltha_x + deltha_y * deltha_y;

	if (result < r) return true;

	return false;
}

//this function checks if the point is in rectangle
bool isInRect(Point p) {
	Point a, d;
	cout << "Please, enter the x coordinate of your first point: ";
	cin >> a.x;
	cout << "Please, enter the y coordinate of your first point: ";
	cin >> a.y;
	cout << "Please, enter the x coordinate of your second point: ";
	cin >> d.x;
	cout << "Please, enter the y coordinate of your second point: ";
	cin >> d.y;

	if (p.x > a.x && p.x < d.x && p.y > a.y && p.y < d.y)
		return true;


	return false;
}

//helping function to calculate the area of a triangle using the coordinates of the points 
float area(Point a, Point b, Point c)
{
	return abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0);
}

//this function checks if the point is in triangle
bool isInTrian(Point p) {
	Point a, b, c;
	cout << "Please, enter the x coordinate of your first point: ";
	cin >> a.x;
	cout << "Please, enter the y coordinate of your first point: ";
	cin >> a.y;
	cout << "Please, enter the x coordinate of your second point: ";
	cin >> b.x;
	cout << "Please, enter the y coordinate of your second point: ";
	cin >> b.y;
	cout << "Please, enter the x coordinate of your third point: ";
	cin >> c.x;
	cout << "Please, enter the y coordinate of your third point: ";
	cin >> c.y;

	float ABC_square = area(a, b, c);

	//let given point is P
	float PBC_square = area(p, b, c);
	float APC_square = area(a, p, c);
	float PAB_square = area(p, a, b);

	return (ABC_square == PBC_square + APC_square + PAB_square);
}

//The function checks if point q lies on line segment 'pr'
// p, q, r- colinrar 
bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;
	return false;
}

int orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // collinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	if (o1 != o2 && o3 != o4) return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;
	// p1, q1 and p2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;
	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;
	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; 
}

//this function checks if the point is in polygon
//in this case it will be used only for hexagones but the algorithm works with all types of poligon
bool isInPoly(Point p, Point polygon[], int n = 6) {

	Point extreme = { INFINITY, p.y };
	int decrease = 0;
	int count = 0, i = 0;

	do {
		int next = (i + 1) % n;
		if (polygon[i].y == p.y) decrease++;

		if (doIntersect(polygon[i], polygon[next], p, extreme))
		{
			// If the point 'p' is collinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (orientation(polygon[i], p, polygon[next]) == 0)
				return onSegment(polygon[i], p, polygon[next]);

			count++;
		}
		i = next;
	} while (i != 0);
	count -= decrease;

	return !(count%2);
}

int main()
{
	Point p;
	cout << "Program to check if a point is in these objects!\n";
	cout << "Please, enter the x coordinate of your point: ";
	cin >> p.x;
	cout << "Please, enter the y coordinate of your point: ";
	cin >> p.y;
	Point polygon1[6] = { {0.5, -2.0}, {2.5, -1.0}, {4.5, 1.0}, {3.5, 3.0}, {0.5, 3.0}, {-0.5, 1.0} };
	Point polygon2[6] = { {-0.5, 1.0}, {0.5, 3.0},  {3.5, 3.0}, {4.5, 1.0}, {2.5, 1.5}, {0.5, -2.0} };


	//circle by given center and radius 
	isInCircle(p) ? cout << "Yes, the point is " : cout << "No, the point is not "; cout << "in the circle!\n";
	//rectangle by given two corner points
	isInRect(p) ? cout << "Yes, the point is " : cout << "No, the point is not "; cout << "in the rectangle!\n";
	//triangle by given three points
	isInTrian(p) ? cout << "Yes, the point is " : cout << "No, the point is not "; cout << "in the triangle!\n";
	//poligon by given coordinates
	isInPoly(p, polygon1) ? cout << "Yes, the point is " : cout << "No, the point is not "; cout << "in the first polygon!\n";
	isInPoly(p, polygon2) ? cout << "Yes, the point is " : cout << "No, the point is not "; cout << "in the second polygon!\n";

	return 0;
}
