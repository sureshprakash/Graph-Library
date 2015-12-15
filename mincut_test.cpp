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

int main()
{
	Graph<int> g(false);
	
	for(int i = 1; i <= 8; i++)
	{
		g.addVertex(i);
	}
	
	g.addEdge(1, 2);
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 8);
	g.addEdge(8, 7);
	g.addEdge(7, 6);
	g.addEdge(6, 5);
	g.addEdge(5, 1);
	
	g.addEdge(2, 6);
	g.addEdge(3, 7);
	
	cout << g << endl;
	
	cout << g.minCut() << endl;
/*	g.mergeVertices(8, 4, 8);
	g.removeSelfLoops();
	cout << g << endl;
	
	g.mergeVertices(3, 7, 3);
	g.removeSelfLoops();
	cout << g << endl;
	
	g.mergeVertices(8, 3, 8);
	g.removeSelfLoops();
	cout << g << endl;
*/	
	return 0;
}
