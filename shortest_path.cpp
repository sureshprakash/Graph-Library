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
	
	pair<vector<int>, vector<vector<int> > > d;
	d = g.shortestPath();
	g.printPath(cout, d);

	return 0;
}
