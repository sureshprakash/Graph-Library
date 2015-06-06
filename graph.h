#ifndef _GRAPH_H
#define _GRAPH_H

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>

using namespace std;

// #define DEBUG

template <class T>
class Edge
{
	public:
		T src, dest;
		int cost;
		
		Edge(T src, T dest, int cost) : src(src), dest(dest), cost(cost)
		{
		}
		
		Edge(const Edge &e)
		{
			this->operator=(e);
		}
		
		void operator=(const Edge &e)
		{
			src = e.src;
			dest = e.src;
			cost = e.cost;
		}
};

template <class T>
class Graph
{
	private:
	
		class Vertex
		{
			private:
				T label;
				multiset<pair<Vertex *, int> > adj;
				multiset<Vertex *> rev; // This is maintained to remove edges, when a vertex, with which the edge is incident on, is removed. It also helps to find the indegree 
				
				typename multiset<pair<Vertex *, int> >::iterator findVertex(Vertex *dest) const;
	
			public:
				Vertex(T label);
				~Vertex();
	
				void setLabel(T label);
				T getLabel() const;
	
				bool checkLabel(T label) const;
				multiset<pair<Vertex *, int> > getAdjacentNodes() const;
				multiset<Vertex *> getReverseNodes() const;
	
				void addEdge(Vertex *dest, int cost);
				bool removeEdge(Vertex *dest, int cost);
				bool removeEdge(Vertex *dest);
				void addEdgesInBatch(multiset<pair<Vertex *, int> > new_adj);
				
				bool edgeExists(Vertex *dest) const;
				bool edgeExists(Vertex *dest, int cost) const;
				
				unsigned int countEdge(Vertex *dest) const;
				unsigned int countEdge(Vertex *dest, int cost) const;
	
				void changeAdjacent(Vertex *dest);
				void removeFromReverse(Vertex *dest);
		};

		set<Vertex *> vertices;
		bool directed;
		
		typename set<Vertex *>::iterator findVertex(T label) const;
	
	public:
		Graph(bool directed);
		Graph(Graph<T> &g);
		~Graph();
		
		bool addVertex(T label);
		bool removeVertex(T label);
		
		bool addEdge(T head, T tail, int cost = 1);
		bool removeEdge(T head, T tail, int cost = 1);
		
		int countEdge(T head, T tail) const;
		int countEdge(T head, T tail, int cost) const;
		
		bool edgeExists(T head, T tail) const;
		bool edgeExists(T head, T tail, int cost) const;
		
		friend ostream &operator<<(ostream &out, const Graph &g)
		{	
			for(typename multiset<Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
			{	
				out << (*v)->getLabel() << " --->  ";
				
				multiset<pair<Vertex *, int> > nbh = (*v)->getAdjacentNodes();
				
				for(typename multiset<pair<Vertex *, int> >::iterator adj = nbh.begin(); adj != nbh.end(); adj++)
				{
					out << (*adj).first->getLabel() << "(" << (*adj).second << "), ";
				}
				
				out << "\b\b " << endl;
			}
			
			#ifdef DEBUG
			for(typename multiset<Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
			{
				multiset<Vertex *> nbh = (*v)->getReverseNodes();
					
				out << (*v)->getLabel() << "(" << nbh.size() << " nodes) --->  ";
				
				for(typename multiset<Vertex *>::iterator adj = nbh.begin(); adj != nbh.end(); adj++)
				{
					out << (*adj)->getLabel() << ", ";
				}
				
				out << "\b\b " << endl;
			}
			#endif
			
			return out;
		}
		
		void operator=(const Graph<T> &g);
		
		void removeSelfLoops();
		
		bool mergeVertices(T first, T second, T new_label);
		
		T pickRandomVertex() const;
		Edge<T> * pickRandomEdge() const;
		
		int minCut();
};


template <class T>
Graph<T>::Vertex::Vertex(T label) : label(label)
{
}

template <class T>
Graph<T>::Vertex::~Vertex()
{
	adj.clear();
	
	// Remove all the edges corresponding to this vertex
	for(typename multiset<Vertex *>::iterator v = this->rev.begin(); v != this->rev.end(); v++)
	{
		(*v)->removeEdge(this);
	}
	
	rev.clear();
}

template <class T>
void Graph<T>::Vertex::setLabel(T label)
{
	this->label = label;
}

template <class T>
T Graph<T>::Vertex::getLabel() const
{
	return label;
}

template <class T>
multiset<pair<typename Graph<T>::Vertex *, int> > Graph<T>::Vertex::getAdjacentNodes() const
{
	return adj;
}

template <class T>
multiset<typename Graph<T>::Vertex *> Graph<T>::Vertex::getReverseNodes() const
{
	return rev;
}

template <class T>
typename multiset<pair<typename Graph<T>::Vertex *, int> >::iterator Graph<T>::Vertex::findVertex(Graph<T>::Vertex *dest) const
{
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if(itr->first == dest)
		{
			return itr;
		}
	}
		
	return adj.end();
}

template <class T>
bool Graph<T>::Vertex::checkLabel(T label) const
{
	return (label == this->label);
}

template <class T>
void Graph<T>::Vertex::addEdge(Graph<T>::Vertex *dest, int cost)
{
	if(dest != NULL)
	{
		this->adj.insert(make_pair(dest, cost));
		dest->rev.insert(this);
	}
}

template <class T>
bool Graph<T>::Vertex::removeEdge(Graph<T>::Vertex *dest, int cost)
{
	typename multiset<pair<Graph<T>::Vertex *, int> >::iterator pos = adj.find(make_pair(dest, cost));
	
	if(pos == adj.end())
	{
		return false;
	}
	
	this->adj.erase(pos); // This is done so that only one copy of the edge is deleted
	dest->rev.erase(dest->rev.find(this));
	
	return true;
}

template <class T>
bool Graph<T>::Vertex::removeEdge(Graph<T>::Vertex *dest)
{
	typename multiset<pair<Graph<T>::Vertex *, int> >::iterator pos = findVertex(dest);
	
	if(pos == adj.end())
	{
		return false;
	}
	
	this->adj.erase(pos); // This is done so that only one copy of the edge is deleted
	dest->rev.erase(dest->rev.find(this));
	
	return true;
}

template <class T>
void Graph<T>::Vertex::addEdgesInBatch(multiset<pair<Graph<T>::Vertex *, int> > new_adj)
{
	// adj.insert() is not used intentionally because, backword pointers are needed for deletion
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator v = new_adj.begin(); v != new_adj.end(); v++)
	{
		addEdge(v->first, v->second);
	}
}

template <class T>
bool Graph<T>::Vertex::edgeExists(Graph<T>::Vertex *dest, int cost) const
{
	return adj.find(make_pair(dest, cost)) != adj.end();
}

template <class T>
unsigned int Graph<T>::Vertex::countEdge(Graph<T>::Vertex *dest, int cost) const
{
	return adj.count(make_pair(dest, cost));
}

template <class T>
bool Graph<T>::Vertex::edgeExists(Graph<T>::Vertex *dest) const
{
	return findVertex(dest) != adj.end();
}

template <class T>
unsigned int Graph<T>::Vertex::countEdge(Graph<T>::Vertex *dest) const
{
	unsigned int count = 0;
	
	for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator itr = adj.begin(); itr != adj.end(); itr++)
	{
		if(itr->first == dest)
		{
			count++;
		}
	}
		
	return count;
}

template <class T>
void Graph<T>::Vertex::changeAdjacent(Graph<T>::Vertex *dest)
{
	for(typename multiset<Graph<T>::Vertex *>::iterator v = this->rev.begin(); v != this->rev.end(); v++)
	{
		typename multiset<pair<Graph<T>::Vertex *, int> >::iterator fd = (*v)->findVertex(this);
		if(fd != (*v)->adj.end())
		{
			(*v)->addEdge(dest, fd->second);
			(*v)->removeEdge(fd->first, fd->second);
		}
	}
}

template <class T>
void Graph<T>::Vertex::removeFromReverse(Graph<T>::Vertex *dest)
{
	vector<typename multiset<Graph<T>::Vertex *>::iterator> vec;
	
	for(typename multiset<Graph<T>::Vertex *>::iterator v = this->rev.begin(); v != this->rev.end(); v++)
	{
		if(*v == dest)
		{
			vec.push_back(v);
		}
	}
	
	const int sz = vec.size();
	
	for(int i = 0; i < sz; i++)
	{
		rev.erase(vec[i]);
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
	for(typename multiset<Vertex *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		delete (*v);
	}
	
	vertices.clear();
}

template <class T>
void Graph<T>::operator=(const Graph<T> &g)
{
	directed = g.directed;

	for(typename set<Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
	{
		vertices.insert(new Vertex((*v)->getLabel()));
	}
	
	for(typename set<Vertex *>::iterator v = g.vertices.begin(); v != g.vertices.end(); v++)
	{
		multiset<pair<Graph<T>::Vertex *, int> > adj = (*v)->getAdjacentNodes();
		
		for(typename multiset<pair<Graph<T>::Vertex *, int> >::iterator a = adj.begin(); a != adj.end(); a++)
		{
			(*findVertex((*v)->getLabel()))->addEdge(*findVertex(a->first->getLabel()), a->second);
		}
	}
}

template <class T>
typename set<typename Graph<T>::Vertex *>::iterator Graph<T>::findVertex(T label) const
{
	for(typename multiset<Graph<T>::Vertex *>::iterator v = vertices.begin(); v != vertices.end(); v++)
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
	
	Vertex *new_node = new Vertex(label);
	
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
	typename set<Graph<T>::Vertex *>::iterator node = findVertex(label);
	
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
bool Graph<T>::addEdge(T head, T tail, int cost)
{	
	typename set<Graph<T>::Vertex *>::iterator hd = findVertex(head);
	typename set<Graph<T>::Vertex *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return false;
	}
	
	(*hd)->addEdge(*tl, cost);
	
	if(!directed)
	{
		if((*hd) != (*tl))		// To avoid adding self loops twice
		{
			(*tl)->addEdge(*hd, cost);
		}
	}
	
	return true;
}

template <class T>
bool Graph<T>::removeEdge(T head, T tail, int cost)
{
	typename set<Graph<T>::Vertex *>::iterator hd = findVertex(head);
	typename set<Graph<T>::Vertex *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return false;
	}
	
	bool forward = true, backword = true;
	
	forward = (*hd)->removeEdge(*tl, cost);
	
	if(!directed)
	{
		if((*hd) != (*tl))		// To avoid removing self loops twice
		{
			backword = (*tl)->removeEdge(*hd, cost);
		}
	}
	
	return (forward && backword);
}

template <class T>
bool Graph<T>::edgeExists(T head, T tail, int cost) const
{
	typename set<Graph<T>::Vertex *>::iterator hd = findVertex(head);
	typename set<Graph<T>::Vertex *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return false;
	}
	
	return (*hd)->edgeExists(*tl, cost);
}

template <class T>
int Graph<T>::countEdge(T head, T tail, int cost) const
{
	typename set<Graph<T>::Vertex *>::iterator hd = findVertex(head);
	typename set<Graph<T>::Vertex *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return -1;
	}
	
	return (*hd)->countEdge(*tl, cost);
}


template <class T>
bool Graph<T>::edgeExists(T head, T tail) const
{
	typename set<Graph<T>::Vertex *>::iterator hd = findVertex(head);
	typename set<Graph<T>::Vertex *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return false;
	}
	
	return (*hd)->edgeExists(*tl);
}

template <class T>
int Graph<T>::countEdge(T head, T tail) const
{
	typename set<Graph<T>::Vertex *>::iterator hd = findVertex(head);
	typename set<Graph<T>::Vertex *>::iterator tl = findVertex(tail);
	
	// One of the lables does not exist
	if((hd == vertices.end()) || (tl == vertices.end()))
	{
		return -1;
	}
	
	return (*hd)->countEdge(*tl);
}

template <class T>
void Graph<T>::removeSelfLoops()
{
	for(typename set<Graph<T>::Vertex *>::iterator v = vertices.begin(); v != vertices.end(); v++)
	{
		while(edgeExists((*v)->getLabel(), (*v)->getLabel()))
		{
			(*v)->removeEdge(*v);
		}
	}
}

template <class T>
bool Graph<T>::mergeVertices(T first, T second, T new_label)
{
	typename set<Graph<T>::Vertex *>::iterator ft = findVertex(first);
	typename set<Graph<T>::Vertex *>::iterator sd = findVertex(second);
	typename set<Graph<T>::Vertex *>::iterator nw = findVertex(new_label);
	
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

	(*ft)->removeFromReverse(*sd);
	
	return true;
}

template <class T>
T Graph<T>::pickRandomVertex() const
{
	int rnd = rand() % vertices.size();
	typename set<Graph<T>::Vertex *>::const_iterator it(vertices.begin());
	advance(it, rnd);
	
	return (*it)->getLabel();
}

template <class T>
Edge<T> * Graph<T>::pickRandomEdge() const
{
	Vertex *hd;
	multiset<pair<Graph<T>::Vertex *, int> > adj;
	int cnt = 0;
	const int double_num_vertices = 4 * vertices.size();
	
	do
	{
		hd = *(findVertex(pickRandomVertex()));
		adj = hd->getAdjacentNodes();
		cnt ++;
	} while((adj.size() == 0) && (cnt < double_num_vertices));

	if(adj.size() == 0)
	{
		cout << "Adjacency list empty" << endl;
		return NULL;
	}
		
	int rnd = rand() % adj.size();
	typename multiset<pair<Graph<T>::Vertex *, int> >::const_iterator it(adj.begin());
	advance(it, rnd);
	
	Vertex *tl = it->first;
	
	return new Edge<T>(hd->getLabel(), tl->getLabel(), it->second);
}

template <class T>
int Graph<T>::minCut()
{
	if(directed)
	{
		return -1;
	}
	
	int rep = 2500;
	int min = vertices.size() + 2;
	
	for(int i = 0; i < rep; i++)
	{
		Graph<T> g = *this;
		
		srand(i);

		g.removeSelfLoops();

		while(g.vertices.size() > 2)
		{		
			Edge<T> * rn = g.pickRandomEdge();
			
			if(rn == NULL)
			{
				break;
			}
			
			g.mergeVertices(rn->src, rn->dest, rn->src);
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
