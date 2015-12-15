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

	vector<int> ts = g.dfs();
	
	cout << "DFS: ";
	for(int i = 0; i < ts.size(); i++)
	{
		cout << ts[i] << ", ";
	}
	
	cout << "\b\b" << endl;
	
	
	ts = g.bfs();
	
	cout << "BFS: ";
	for(int i = 0; i < ts.size(); i++)
	{
		cout << ts[i] << ", ";
	}
	
	cout << "\b\b" << endl;
	
	ts = g.dfs(4);
	
	cout << "DFS starting from 4: ";
	for(int i = 0; i < ts.size(); i++)
	{
		cout << ts[i] << ", ";
	}
	
	cout << "\b\b" << endl;
	
	
	ts = g.bfs(4);
	
	cout << "BFS starting from 4: ";
	for(int i = 0; i < ts.size(); i++)
	{
		cout << ts[i] << ", ";
	}
	
	cout << "\b\b" << endl;

	Graph<char> g1(false);
	
	g1.addVertex('A');
	g1.addVertex('B');
	g1.addVertex('C');
	g1.addVertex('D');

	g1.addEdge('A', 'B');
	g1.addEdge('B', 'C');
	g1.addEdge('C', 'D');
	g1.addEdge('D', 'A');
	
	cout << "Hop distances:\n";
	char src = 'A';
	map<char, unsigned int> dist = g1.hop_distance(src);
	for(map<char, unsigned int>::iterator itr = dist.begin(); itr != dist.end(); itr++)
	{
		cout << itr->first << " is " << itr->second << " hop(s) away from " << src << endl;
	}

	cout << "Directed: " << g.isDirected() << endl;
	cout << "Connected: " << g.isConnected() << endl;
	cout << "Simple: " << g.isSimple() << endl;
	cout << "Acyclic: " << g.isAcyclic() << endl;

	cout << "Directed: " << g1.isDirected() << endl;
	cout << "Connected: " << g1.isConnected() << endl;
	cout << "Simple: " << g1.isSimple() << endl;
	cout << "Acyclic: " << g1.isAcyclic() << endl;
	
	return 0;
}
