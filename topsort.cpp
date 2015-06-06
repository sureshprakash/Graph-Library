#include "graph.h"
#include <iostream>

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

	vector<int> ts;
	
	try
	{	
		ts = g.topologicalSort();
	}
	catch(const char *err)
	{
		cout << err << endl;
	}
	
	cout << "Topological ordering: " << endl;
	for(int i = 0; i < ts.size(); i++)
	{
		cout << ts[i] << ", ";
	}
	
	cout << "\b\b" << endl;
	
	return 0;
}
