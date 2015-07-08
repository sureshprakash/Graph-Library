#include <iostream>

#include "graph.h"

using namespace std;

int main()
{
	Graph<char> g(true);
	
	g.addVertex('A');
	g.addVertex('B');
	g.addVertex('C');
	g.addVertex('D');
	
	g.addEdge('A', 'B');
	g.addEdge('A', 'C');
	g.addEdge('B', 'C');
	g.addEdge('C', 'D');
	g.addEdge('D', 'B');
	
	cout << g.pathExists('A', 'D') << endl;
	cout << g.pathExists('B', 'D') << endl;
	cout << g.pathExists('C', 'D') << endl;
	cout << g.pathExists('C', 'A') << endl;
	
	return 0;
}

