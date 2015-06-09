#include "graph.h"

#include <iostream>

using namespace std;

int main()
{
	Graph<int> g(false);
	
	g.addVertex(1);
	g.addVertex(2);
	g.addVertex(3);
	g.addVertex(4);
	g.addVertex(5);
	g.addVertex(6);
	g.addVertex(7);
	g.addVertex(8);
	g.addVertex(9);
	g.addVertex(10);
	
	g.addEdge(1, 2, 3);
	g.addEdge(2, 3, 5);
	g.addEdge(1, 3, 4);
	
	g.addEdge(4, 5, 9);
	
	g.addEdge(6, 7, 13);
	g.addEdge(8, 7, 15);
	g.addEdge(9, 7, 16);
	g.addEdge(9, 10, 19);

	vector<int> vert = g.getVertices();
	
	for(int i = 0; i < vert.size(); i++)
	{
		cout << vert[i] << ", ";
	}
	
	cout << endl;
	
	vector<pair<int, pair<int, int> > > edges = g.getEdges();
	
	for(int i = 0; i < edges.size(); i++)
	{
		cout << edges[i].first << " " << edges[i].second.first << " " << edges[i].second.second << endl;
	}
	
	cout << endl;
	
	vector<Graph<int> > comp = g.getConnectedComponents();
	
	for(int i = 0; i < comp.size(); i++)
	{
		cout << comp[i] << endl;
	}
	
	return 0;
}
