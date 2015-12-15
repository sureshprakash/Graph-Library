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
	
	g.addEdge('A', 'A', 1);
	g.addEdge('A', 'B', 2);
	g.addEdge('A', 'B', 3);
	g.addEdge('B', 'B', 4);
	g.addEdge('B', 'B', 5);
	g.addEdge('A', 'C', 6);
	g.addEdge('C', 'A', 7);
	g.addEdge('D', 'B', 8);
	g.addEdge('C', 'D', 9);
	g.addEdge('D', 'C', 10);
	g.addEdge('D', 'C', 11);
	g.addEdge('C', 'D', 12);
	
	// Test for invalid vertices
	g.addEdge('A', 'F', 13);
	g.addEdge('E', 'B', 14);
	g.addEdge('G', 'H', 15);
	
	cout << "---------------------- Original graph ------------------------" << endl;
	cout << g << endl;
	
	g.removeEdge('B', 'B', 5);
	g.removeEdge('A', 'A', 1);
	g.removeEdge('A', 'C', 6);
	g.removeEdge('C', 'D', 9);
	g.removeEdge('D', 'C', 11);
	
	cout << "------------------- Removed two self loops, one single link and one double link -----------------" << endl;
	cout << g << endl;
	
	g.addEdge('B', 'B', 5);
	g.addEdge('A', 'A', 1);
	g.addEdge('A', 'C', 6);
	g.addEdge('C', 'D', 9);
	g.addEdge('D', 'C', 11);
	
	cout << "---------------------- Removed edges are added back -----------------------------------------" << endl;
	cout << g << endl;
	
	g.removeVertex('B');
	g.removeVertex('E'); // Remove non existing vertex
	
	cout << "---------------------- Vertex B removed -----------------------------------------------------" << endl;
	cout << g << endl;
	
	g.addVertex('B');
	
	cout << "---------------------- Vertex B added back --------------------------------------------------" << endl;
	cout << g << endl;
	
	g.addEdge('A', 'B', 15);
	g.addEdge('A', 'B', 15);
	g.addEdge('B', 'B', 17);
	g.addEdge('B', 'B', 17);
	g.addEdge('D', 'B', 19);
	
	cout << "---------------------- Edges with B are recreated -------------------------------------------" << endl;
	cout << g << endl;

	cout << "Min-cut: " << g.minCut() << endl;
	
	cout << "Edge existency check: " << endl;
	cout << "A, A = " << g.edgeExists('A', 'A', 1) << endl;
	cout << "A, B = " << g.edgeExists('A', 'B', 15) << endl;
	cout << "B, B = " << g.edgeExists('B', 'B', 17) << endl;
	cout << "A, C = " << g.edgeExists('A', 'C', 6) << endl;
	cout << "C, A = " << g.edgeExists('C', 'A', 7) << endl;
	cout << "D, B = " << g.edgeExists('D', 'B', 19) << endl;
	cout << "C, D = " << g.edgeExists('C', 'D', 9) << endl;
	cout << "D, C = " << g.edgeExists('D', 'C', 11) << endl;
	cout << "A, D = " << g.edgeExists('A', 'D', 12) << endl;
	cout << "B, C = " << g.edgeExists('B', 'C', 12) << endl;
	cout << "B, D = " << g.edgeExists('B', 'D', 12) << endl;
	cout << "C, C = " << g.edgeExists('C', 'C', 12) << endl;
	cout << "D, D = " << g.edgeExists('D', 'D') << endl;
	cout << "E, D = " << g.edgeExists('E', 'D') << endl;
	
	cout << "Edge counts: " << endl;
	cout << "A, A = " << g.countEdge('A', 'A', 1) << endl;
	cout << "A, B = " << g.countEdge('A', 'B', 15) << endl;
	cout << "B, B = " << g.countEdge('B', 'B', 17) << endl;
	cout << "A, C = " << g.countEdge('A', 'C', 6) << endl;
	cout << "C, A = " << g.countEdge('C', 'A', 7) << endl;
	cout << "D, B = " << g.countEdge('D', 'B', 19) << endl;
	cout << "C, D = " << g.countEdge('C', 'D', 9) << endl;
	cout << "D, C = " << g.countEdge('D', 'C', 11) << endl;
	cout << "A, D = " << g.countEdge('A', 'D', 12) << endl;
	cout << "B, C = " << g.countEdge('B', 'C', 12) << endl;
	cout << "B, D = " << g.countEdge('B', 'D', 12) << endl;
	cout << "C, C = " << g.countEdge('C', 'C', 12) << endl;
	cout << "D, D = " << g.countEdge('D', 'D') << endl;
	cout << "E, D = " << g.countEdge('E', 'D') << endl;

	g.mergeVertices('A', 'B', 'E');
	
	cout << "----------------------------- A and B are merged to E -------------------" << endl;
	cout << g << endl;
		
	g.removeSelfLoops();
	
	cout << "-------------------------- All self loops are removed -------------------" << endl;
	cout << g << endl;
	
	cout << "Indegree of C: " << g.indegree('C') << endl;
	cout << "Indegree of D: " << g.indegree('D') << endl;
	cout << "Indegree of E: " << g.indegree('E') << endl;
	cout << "Indegree of A: " << g.indegree('A') << endl;	

	cout << "Outdegree of C: " << g.outdegree('C') << endl;
	cout << "Outdegree of D: " << g.outdegree('D') << endl;
	cout << "Outdegree of E: " << g.outdegree('E') << endl;
	cout << "Outdegree of F: " << g.outdegree('F') << endl;	
	
	cout << "Number of vertices: " << g.numVertices() << endl;
	cout << "Number of edges: " << g.numEdges() << endl;

	return 0;
}
