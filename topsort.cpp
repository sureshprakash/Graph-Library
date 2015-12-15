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
