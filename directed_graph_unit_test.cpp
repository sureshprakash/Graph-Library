#include <iostream>

#include "graph.h"

int main(int argc, char *argv[])
{
	Graph<char> g(true);

	g.addVertex('A');
	g.addVertex('B');
	g.addVertex('C');
	g.addVertex('D');
	
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
	
	
	
	return 0;
}
