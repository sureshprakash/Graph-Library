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

