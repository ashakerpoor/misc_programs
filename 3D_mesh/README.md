# Point-in-Triangular-Mesh

This C++ program reads the vertex coordinates of a triangular mesh, along with the number of triangles, and the coordinates of a point from text files. It determines whether the point is inside the triangular mesh.

## Prerequisites

- C++ compiler (supporting C++11 or later)
- Text files containing the triangular mesh data (vertices and triangles) as well as the coordinates of the point.

## Usage

1. Clone the repository or download the source code files.
2. Compile the program using a C++ compiler. For example:
   --shell
   g++ mesh.cpp -o point_in_mesh

## Data Format

1. Prepare a text file (named 'mesh.dat') containing the triangular mesh data in the following format:<br>
   &lt;x11&gt; &lt;y11&gt; &lt;z11&gt; &lt;x12&gt; &lt;y12&gt; &lt;z12&gt; &lt;x13&gt; &lt;y13&gt; &lt;z13&gt;,<br>
   ...<br>
   &lt;xN1&gt; &lt;yN1&gt; &lt;zN1&gt; &lt;xN2&gt; &lt;yN2&gt; &lt;zN2&gt; &lt;xN3&gt; &lt;yN3&gt; &lt;zN3&gt;,<br>
   corresponding to N triangles defined.
2. Prepare a text file (named 'point.dat') containing the number of triangles and the coords of the point:<br>
   number of triangles,<br>
   &lt;px&gt; &lt;py&gt; &lt;pz&gt;

