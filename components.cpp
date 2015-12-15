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

#include "graph.h"

#include <iostream>

using namespace std;

int main()
{
	// Undirected test
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
	
	vector<Edge<int> *> edges = g.getEdges();
	
	for(int i = 0; i < edges.size(); i++)
	{
		cout << edges[i]->src << " " << edges[i]->dest << " " << edges[i]->cost << endl;
	}
	
	cout << endl;
	
	vector<Graph<int> * > comp = g.getConnectedComponents();
	
	for(int i = 0; i < comp.size(); i++)
	{
		cout << (*comp[i]) << endl;
	}

	// Directed test
	Graph<int> g1(true);
	
	g1.addVertex(1);
	g1.addVertex(2);
	g1.addVertex(3);
	g1.addVertex(4);
	g1.addVertex(5);
	g1.addVertex(6);
	g1.addVertex(7);
	g1.addVertex(8);
	g1.addVertex(9);
	g1.addVertex(10);
	g1.addVertex(11);
	
	g1.addEdge(1, 2, 3);
	g1.addEdge(2, 3, 5);
	g1.addEdge(3, 1, 4);
	
	g1.addEdge(2, 4, 9);
	
	g1.addEdge(7, 6, 13);
	g1.addEdge(7, 8, 15);
	g1.addEdge(5, 7, 16);
	g1.addEdge(6, 5, 19);
	g1.addEdge(8, 5, 3);
	g1.addEdge(3, 5);
	g1.addEdge(3, 6);
	
	g1.addEdge(5, 9, 13);
	g1.addEdge(4, 9, 15);
	g1.addEdge(8, 11, 16);
	g1.addEdge(4, 10, 19);
	g1.addEdge(9, 10, 3);
	g1.addEdge(10, 11);
	g1.addEdge(11, 9);

	vert = g1.getVertices();
	
	for(int i = 0; i < vert.size(); i++)
	{
		cout << vert[i] << ", ";
	}
	
	cout << endl;
	
	edges = g1.getEdges();
	
	for(int i = 0; i < edges.size(); i++)
	{
		cout << (*edges[i]);
	}
	
	cout << endl;
	
	comp = g1.getConnectedComponents();
	
	for(int i = 0; i < comp.size(); i++)
	{
		cout << (*comp[i]) << endl;
	}

	return 0;
}
