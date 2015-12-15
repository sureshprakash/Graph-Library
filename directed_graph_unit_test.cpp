/**
Implementation of Graph algorithms in one single class
Copyright (C) Suresh P (sureshsonait@gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**/

#include <iostream>

#include "graph.h"

int main(int argc, char *argv[])
{
	Graph<char> g(true);

	g.addVertex('A');
	g.addVertex('B');
	g.addVertex('C');
	g.addVertex('D');
	g.addVertex('A'); // Redundancy check
	
	/*
-----	          ====
|	|            ||  ||
|   V            V   ||
----A =========> B ===
	^            ^
	|            |
	|            |
	V            |
	C<==========>D
	
	Description: A has 1 self loop
	             A is connected to B by a double link
	             B has a double self loop
				 A and C are connected with each other by a single link
				 C and D are connected with each other with a double link
				 D is connected to B by a single link
	*/
	
	g.addEdge('A', 'A');
	g.addEdge('A', 'B');
	g.addEdge('A', 'B');
	g.addEdge('B', 'B');
	g.addEdge('B', 'B');
	g.addEdge('A', 'C');
	g.addEdge('C', 'A');
	g.addEdge('D', 'B');
	g.addEdge('C', 'D');
	g.addEdge('D', 'C');
	g.addEdge('D', 'C');
	g.addEdge('C', 'D');
	
	// Test for invalid vertices
	g.addEdge('A', 'F');
	g.addEdge('E', 'B');
	g.addEdge('G', 'H');
	
	cout << "---------------------- Original graph ------------------------" << endl;
	cout << g << endl;
	
	g.removeEdge('B', 'B');
	g.removeEdge('A', 'A');
	g.removeEdge('A', 'C');
	g.removeEdge('C', 'D');
	g.removeEdge('D', 'C');
	
	cout << "------------------- Removed two self loops, one single link and one double link -----------------" << endl;
	cout << g << endl;
	
	g.addEdge('B', 'B');
	g.addEdge('A', 'A');
	g.addEdge('A', 'C');
	g.addEdge('C', 'D');
	g.addEdge('D', 'C');
	
	cout << "---------------------- Removed edges are added back -----------------------------------------" << endl;
	cout << g << endl;
	
	g.removeVertex('B');
	g.removeVertex('E'); // Remove non existing vertex
	
	cout << "---------------------- Vertex B removed -----------------------------------------------------" << endl;
	cout << g << endl;
	
	g.addVertex('B');
	
	cout << "---------------------- Vertex B added back --------------------------------------------------" << endl;
	cout << g << endl;
	
	g.addEdge('A', 'B');
	g.addEdge('A', 'B');
	g.addEdge('B', 'B');
	g.addEdge('B', 'B');
	g.addEdge('D', 'B');
	
	cout << "---------------------- Edges with B are recreated -------------------------------------------" << endl;
	cout << g << endl;
	
	cout << "Edge existency check: " << endl;
	cout << "A, A = " << g.edgeExists('A', 'A') << endl;
	cout << "A, B = " << g.edgeExists('A', 'B') << endl;
	cout << "B, B = " << g.edgeExists('B', 'B') << endl;
	cout << "A, C = " << g.edgeExists('A', 'C') << endl;
	cout << "C, A = " << g.edgeExists('C', 'A') << endl;
	cout << "D, B = " << g.edgeExists('D', 'B') << endl;
	cout << "C, D = " << g.edgeExists('C', 'D') << endl;
	cout << "D, C = " << g.edgeExists('D', 'C') << endl;
	cout << "A, D = " << g.edgeExists('A', 'D') << endl;
	cout << "B, C = " << g.edgeExists('B', 'C') << endl;
	cout << "B, D = " << g.edgeExists('B', 'D') << endl;
	cout << "C, C = " << g.edgeExists('C', 'C') << endl;
	cout << "D, D = " << g.edgeExists('D', 'D') << endl;
	cout << "E, D = " << g.edgeExists('E', 'D') << endl;
	
	cout << "Edge counts: " << endl;
	cout << "A, A = " << g.countEdge('A', 'A') << endl;
	cout << "A, B = " << g.countEdge('A', 'B') << endl;
	cout << "B, B = " << g.countEdge('B', 'B') << endl;
	cout << "A, C = " << g.countEdge('A', 'C') << endl;
	cout << "C, A = " << g.countEdge('C', 'A') << endl;
	cout << "D, B = " << g.countEdge('D', 'B') << endl;
	cout << "C, D = " << g.countEdge('C', 'D') << endl;
	cout << "D, C = " << g.countEdge('D', 'C') << endl;
	cout << "A, D = " << g.countEdge('A', 'D') << endl;
	cout << "B, C = " << g.countEdge('B', 'C') << endl;
	cout << "B, D = " << g.countEdge('B', 'D') << endl;
	cout << "C, C = " << g.countEdge('C', 'C') << endl;
	cout << "D, D = " << g.countEdge('D', 'D') << endl;
	cout << "E, D = " << g.countEdge('E', 'D') << endl;
	
	return 0;
}
