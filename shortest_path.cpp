#include <iostream>

#include "graph.h"

using namespace std;

int main()
{
	Graph<int> g(true);
	
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addVertex(5);
	g.addVertex(6);
	g.addVertex(7);
	g.addVertex(8);
		
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(1, 4);
	
	g.addEdge(2, 4);
	g.addEdge(2, 5);
	
//	g.addEdge(3, 4);
	
	g.addEdge(4, 3);
	g.addEdge(4, 5);
	g.addEdge(4, 6);
	g.addEdge(4, 7);
	
	g.addEdge(5, 7);
	
	g.addEdge(6, 3);
	g.addEdge(6, 7);

	cout << g << endl;

	map<int, pair<int, int> > p;
/*
	p = g.bfsShortestPath(1);
	g.printPath(cout, p);	
	
	p = g.topologicalShortestPath(1);
	g.printPath(cout, p);

	p = g.dijkstraShortestPath(1);
	g.printPath(cout, p);
	
	p = g.bellmanFordShortestPath(1);
	g.printPath(cout, p);
*/
	p = g.shortestPath(1);
	g.printPath(cout, p);
	
	pair<vector<int>, vector<vector<pair<int, int> > > >  d;
	d = g.shortestPath();

	g.printPath(cout, d);
	
	Graph<char> g1(false);
	
	g1.addVertex('a');
	g1.addVertex('b');
	g1.addVertex('c');
	g1.addVertex('d');
	g1.addVertex('e');
	g1.addVertex('f');
	g1.addVertex('g');
	
	g1.addEdge('a', 'b', 2);
	g1.addEdge('a', 'c', 3);
	g1.addEdge('a', 'd', 7);
	g1.addEdge('b', 'e', 1);
	g1.addEdge('b', 'd', 8);
	g1.addEdge('c', 'd', 12);
	g1.addEdge('d', 'e', 9);
	g1.addEdge('d', 'f', 11);
	g1.addEdge('d', 'g', 6);
	g1.addEdge('c', 'f', 4);
	g1.addEdge('g', 'f', 5);
	g1.addEdge('e', 'g', 10);
	
	cout << g1 << endl;
	
	Graph<char> tree = g1.minimumSpanningTree();
	cout << tree << endl;

	return 0;
}
