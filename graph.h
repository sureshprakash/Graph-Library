/*

	Warning: This graph implementation is not complete. Suddenly, all set<T> were converted to multiset<T>. However, the entire code was written considering set in mind. So, careful using the code
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <algorithm>
#include <cstdio>
#include <set>

using namespace std;

template <class T>
class Vertex
{
	private:
		T label;
		multiset<Vertex<T> *> adj;
		multiset<Vertex<T> *> rev; // This is maintained to remove edges, when a vertex, with which the edge is incident on, is removed
		
	public:
		Vertex(T label);
		~Vertex();
		
		void setLabel(T label);
		T getLabel() const;
		
		bool checkLabel(T label) const;
		multiset<Vertex<T> *> getAdjacentNodes() const;
		
		void addEdge(Vertex<T> *dest);
		bool removeEdge(Vertex<T> *dest);
		void addEdgesInBatch(multiset<Vertex<T> *> new_adj);
		bool edgeExists(Vertex<T> *dest) const;
		
		void changeAdjacent(Vertex<T> *dest);
};

template <class T>
class Graph
{
	private:
		multiset<Vertex<T> *> vertices;
		bool directed;
		
		typename multiset<Vertex<T> *>::iterator findVertex(T label) const;
	
	public:
		Graph(bool directed);
		Graph(Graph<T> &g);
		~Graph();
		
		bool addVertex(T label);
		bool removeVertex(T label);
		
		bool addEdge(T head, T tail);
		bool removeEdge(T head, T tail);
		
		bool edgeExists(T head, T tail) const;
		
		friend ostream &operator<<(ostream &out, const Graph &g)
		{	
			for(typename multiset<Vertex<T> *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
			{	
				out << (*v)->getLabel() << " --->  ";
				
				multiset<Vertex<T> *> nbh = (*v)->getAdjacentNodes();
				
				for(typename multiset<Vertex<T> *>::iterator adj = nbh.begin(); adj != nbh.end(); adj++)
				{
					out << (*adj)->getLabel() << ", ";
				}
				
				out << "\b\b " << endl;
			}
			
			return out;
		}
		
		void operator=(const Graph<T> &g);
		
		void removeSelfLoops();
		
		bool mergeVertices(T first, T second, T new_label);
		
		T pickRandomVertex() const;
		pair<T, T> pickRandomEdge() const;
		
		int findMinCut();
};


template <class T>
Vertex<T>::Vertex(T label) : label(label)
{
}

template <class T>
Vertex<T>::~Vertex()
{
	adj.clear();
	
	// Remove all the edges corresponding to this vertex
	for(typename multiset<Vertex<T> *>::iterator v = this->rev.begin(); v != this->rev.end(); v++)
	{
		(*v)->removeEdge(this);
	}
	
	rev.clear();
}

template <class T>
void Vertex<T>::setLabel(T label)
{
	this->label = label;
}

template <class T>
T Vertex<T>::getLabel() const
{
	return label;
}

template <class T>
multiset<Vertex<T> *> Vertex<T>::getAdjacentNodes() const
{
	return adj;
}

template <class T>
bool Vertex<T>::checkLabel(T label) const
{
	return (label == this->label);
}

template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest)
{
	if(dest != NULL)
	{
		this->adj.insert(dest);
		dest->rev.insert(this);
	}
}

template <class T>
bool Vertex<T>::removeEdge(Vertex<T> *dest)
{
	if(adj.find(dest) == adj.end())
	{
		return false;
	}
	
	this->adj.erase(dest);
	dest->rev.erase(this);
	
	return true;
}

template <class T>
void Vertex<T>::addEdgesInBatch(multiset<Vertex<T> *> new_adj)
{
	// adj.insert() is not used intentionally because, backword pointers are needed for deletion
	for(typename multiset<Vertex<T> *>::iterator v = new_adj.begin(); v != new_adj.end(); v++)
	{
		addEdge(*v);
	}
}

template <class T>
bool Vertex<T>::edgeExists(Vertex<T> *dest) const
{
	return (adj.find(dest) != adj.end());
}

template <class T>
void Vertex<T>::changeAdjacent(Vertex<T> *dest)
{
	for(typename multiset<Vertex<T> *>::iterator v = this->rev.begin(); v != this->rev.end(); v++)
	{
		typename multiset<Vertex<T> *>::iterator fd = (*v)->adj.find(this);
		if(fd != (*v)->adj.end())
		{
			(*v)->adj.erase(fd);
			(*v)->adj.insert(dest);
		}
	}
}

template <class T>
Graph<T>::Graph(bool directed) : directed(directed)
{
}

template <class T>
Graph<T>::Graph(Graph<T> &g)
{
	this->operator=(g);
}

template <class T>
Graph<T>::~Graph()
{
	for(typename multiset<Vertex<T> *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		delete (*v);
	}
	
	vertices.clear();
}

template <class T>
void Graph<T>::operator=(const Graph<T> &g)
{
	directed = g.directed;
	for(typename multiset<Vertex<T> *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
	{
		vertices.insert(*v);
	}
}

template <class T>
typename multiset<Vertex<T> *>::iterator Graph<T>::findVertex(T label) const
{
	for(typename multiset<Vertex<T> *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		if((*v)->checkLabel(label))
		{
			return v;
		}
	}
	
	return vertices.end();
}

template <class T>
bool Graph<T>::addVertex(T label)
{
	// Node with same name already exists
	if(findVertex(label) != vertices.end())
	{
		return false;
	}
	
	Vertex<T> *new_node = new Vertex<T>(label);
	
	// Memory full
	if(new_node == NULL)
	{
		return false;
	}
	
	vertices.insert(new_node);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(T label)
{
	typename multiset<Vertex<T> *>::iterator node = findVertex(label);
	
	// Label does not exist
	if(node == vertices.end())
	{
		return false;
	}

	delete (*node);
	vertices.erase(node);
	
	return true;
}

template <class T>
bool Graph<T>::addEdge(T head, T tail)
{	
	typename multiset<Vertex<T> *>::iterator hd = findVertex(head);
	typename multiset<Vertex<T> *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return false;
	}
	
	(*hd)->addEdge(*tl);
	
	if(!directed)
	{
		if((*hd) != (*tl))		// To avoid adding self loops twice
		{
			(*tl)->addEdge(*hd);
		}
	}
	
	return true;
}

template <class T>
bool Graph<T>::removeEdge(T head, T tail)
{
	typename multiset<Vertex<T> *>::iterator hd = findVertex(head);
	typename multiset<Vertex<T> *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return false;
	}
	
	bool forward = true, backword = true;
	
	forward = (*hd)->removeEdge(*tl);
	
	if(!directed)
	{
		if((*hd) != (*tl))		// To avoid adding self loops twice
		{
			backword = (*tl)->removeEdge(*hd);
		}
	}
	
	return (forward && backword);
}

template <class T>
bool Graph<T>::edgeExists(T head, T tail) const
{
	typename multiset<Vertex<T> *>::iterator hd = findVertex(head);
	typename multiset<Vertex<T> *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return false;
	}
	
	return (*hd)->edgeExists(*tl);
}

template <class T>
void Graph<T>::removeSelfLoops()
{
	for(typename multiset<Vertex<T> *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{	
		removeEdge((*v)->getLabel(), (*v)->getLabel());
	}
}

template <class T>
bool Graph<T>::mergeVertices(T first, T second, T new_label)
{
	typename multiset<Vertex<T> *>::iterator ft = findVertex(first);
	typename multiset<Vertex<T> *>::iterator sd = findVertex(second);
	typename multiset<Vertex<T> *>::iterator nw = findVertex(new_label);
	
	// One of the lables does not exist
	if((ft == vertices.end()) || (sd == vertices.end()))
	{
		return false;
	}
	
	// Cannot merge a vertex with itself
	if((*ft) == (*sd))
	{	
		return false;
	}
	
	// Node with same name already exists (and it does not match with one of the nodes being merged
	if((nw != vertices.end()) && (ft != nw) && (sd != nw))
	{
		return false;
	}
	
	(*ft)->setLabel(new_label);
	(*ft)->addEdgesInBatch((*sd)->getAdjacentNodes());
	
	(*sd)->changeAdjacent(*ft);
	
	delete (*sd);
	vertices.erase(sd);
	
	return true;
}

template <class T>
T Graph<T>::pickRandomVertex() const
{
	int rnd = rand() % vertices.size();
	typename multiset<Vertex<T> *>::const_iterator it(vertices.begin());
	advance(it, rnd);
	
	return (*it)->getLabel();
}

template <class T>
pair<T, T> Graph<T>::pickRandomEdge() const
{
	Vertex<T> *hd;
	multiset<Vertex<T> *> adj;
	int cnt = 0;
	const int double_num_vertices = 4 * vertices.size();
	
	do
	{
		hd = *(findVertex(pickRandomVertex()));
		adj = hd->getAdjacentNodes();
		cnt ++;
	} while((adj.size() != 0) && (cnt < double_num_vertices));

	if(adj.size() == 0)
	{
		cout << "Adjacency list empty" << endl;
	}
		
	int rnd = rand() % adj.size();
	typename multiset<Vertex<T> *>::const_iterator it(adj.begin());
	advance(it, rnd);
	
	Vertex<T> *tl = *it;
	
	return make_pair(hd->getLabel(), tl->getLabel());
}

template <class T>
int Graph<T>::findMinCut()
{
	int rep = 2500;
	int min = vertices.size() + 2;
	
	for(int i = 0; i < rep; i++)
	{
		Graph<T> g = *this;
		
		srand(i);

		while(g.vertices.size() > 2)
		{		
			pair<char, char> rn = g.pickRandomEdge();
		
			g.mergeVertices(rn.first, rn.second, rn.first);
		
			g.removeSelfLoops();
		}

		if(g.vertices.size() == 2)
		{
			int loc_min = (*g.vertices.begin())->getAdjacentNodes().size();
			
			if(loc_min < min)
			{
				min = loc_min;
			}
		}	
	}
	
	return min;
}

#endif
