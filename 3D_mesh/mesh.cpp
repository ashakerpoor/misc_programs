/*
* This program reads in the followings from separate text files:
* 1) The number of defined triangles in the mesh.
* 2) The Cartesian coordinates of a point in a 3D space.
* 3) The Cartesian coordinates of vertices of N triangles
*    that make a 3-dimensional mesh in space.
* The program determines whether the point is inside the triangular mesh.
*/

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#define EPSILON 1e-6

using namespace std;

class point3d {
public:
	float x;
	float y;
	float z;
};

class triangle {
public:
	point3d v0;
	point3d v1;
	point3d v2;
};

// we determine if the ray intersects the triangle using the Moller-Trumbore algorithm.
bool ray_intersects_mesh(point3d origin, point3d direction, triangle surface) {
        point3d edge1, edge2, h, s, q;
        float a, f, u, v, t;

        // compute the edges of the triangle.
        edge1.x = surface.v1.x - surface.v0.x;
        edge1.y = surface.v1.y - surface.v0.y;
        edge1.z = surface.v1.z - surface.v0.z;
        edge2.x = surface.v2.x - surface.v0.x;
        edge2.y = surface.v2.y - surface.v0.y;
        edge2.z = surface.v2.z - surface.v0.z;

        // compute the cross product of direction vector and Edge2: h = (direction x Edge2).
        h.x = direction.y * edge2.z - direction.z * edge2.y;
        h.y = direction.z * edge2.x - direction.x * edge2.z;
        h.z = direction.x * edge2.y - direction.y * edge2.x;

        // compute the dot product of Edge1 and h: a = (h.Edge1).
        a = edge1.x * h.x + edge1.y * h.y + edge1.z * h.z;

        // check if ray is parallel or nearly parallel to the triangle.
        if (fabs(a) < EPSILON) return false;

        // compute the vector from the origin of the ray 
        // to the first vertex of the triangle.
        s.x = origin.x - surface.v0.x;
        s.y = origin.y - surface.v0.y;
        s.z = origin.z - surface.v0.z;

        // calculate the dot product of s and h.
        f = 1. / a;
        u = f * (s.x * h.x + s.y * h.y + s.z * h.z);

        // check if the intersection point is outside the triangle.
        if (u < 0.0 || u > 1.0) return false;

        q.x = s.y * edge1.z - s.z * edge1.y;
        q.y = s.z * edge1.x - s.x * edge1.z;
        q.z = s.x * edge1.y - s.y * edge1.x;

        v = f * (direction.x * q.x + direction.y * q.y + direction.z * q.z);

        // check if the intersection point is outside the triangle.
        if (v < 0.0 || u + v > 1.0) return false;

        // parameter t is used to find the intersection point.
        t = f * (edge2.x * q.x + edge2.y * q.y + edge2.z * q.z);

        if (t > EPSILON) return true;

        return false;
}

// function to determine if a point is inside the triangular mesh.
bool is_point_inside(point3d point, vector<triangle>& mesh, int n_triangles) {
        point3d origin;
        int i, count;

        origin.x = point.x + 100.0; // define origin as a point far from the 'Point'.
        origin.x = point.y;
        origin.z = point.z;

        count = 0;
        for (i = 0; i < n_triangles; i++) {
                if (ray_intersects_mesh(origin, point, mesh[i]))
                        count++;
        }

        return (count % 2) == 1;
}


int main() 
{

int n_triangles;
point3d point;
triangle Triangle;
vector<triangle> mesh;
string line;
ifstream file;
istringstream iss;


file.open("point.dat");
if (!file) {
        cerr << "Failed to open the 'point.dat' file." << endl;
        return 1;
}


getline(file, line);
iss.str(line);
if (!(iss >> n_triangles)) {
        cerr << "Error reading # of triangles from the file." << endl;
}
iss.clear(); // clear any error flags and prepare for the next line.
cout << "Number of triangles == " << n_triangles << endl;


getline(file, line);
iss.str(line);
if (!(iss >> point.x >> point.y >> point.z)) {
        cerr << "Error reading coords of the point." << endl;
}
iss.clear();
file.close();


file.open("mesh.dat");
if (!file) {
	cerr << "Failed to open the 'mesh.dat' file." << endl;
	return 1;
}


//cout << "The coordinates of the vertices are:" << endl;
while (getline(file, line)) {
	if (line.empty() || line[0] == '#') continue;

	iss.str(line);
	if (!(iss >> Triangle.v0.x >> Triangle.v0.y >> Triangle.v0.z >>
		Triangle.v1.x >> Triangle.v1.y >> Triangle.v1.z >>
		Triangle.v2.x >> Triangle.v2.y >> Triangle.v2.z)) {
	cerr << "Error reading coordinates from the file." << endl;
	break;  // Exit the loop if there's an error
	}
	mesh.push_back(Triangle);
	iss.clear();

	cout << Triangle.v0.x << " " << Triangle.v0.y << " " << Triangle.v0.z << " " <<
		Triangle.v1.x << " " << Triangle.v1.y << " " << Triangle.v1.z << " " <<
		Triangle.v2.x << " " << Triangle.v2.y << " " << Triangle.v2.z << endl;
}
file.close();


bool is_inside = is_point_inside(point, mesh, n_triangles);
if (is_inside)
	cout << "Point (" << point.x << ", " << point.y << ", " << point.z << ")" <<
		" is inside the triangular mesh." << endl;
else
	cout << "Point (" << point.x << ", " << point.y << ", " << point.z << ")" <<
                " is outside the triangular mesh." << endl;

return 0;
}
