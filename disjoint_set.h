#ifndef _DISJOINT_SET
#define _DISJOINT_SET

#include <iostream>
#include <map>

using namespace std;

template<class T>
class DisjointSet  // Weighted quick union + Path compression
{
	private:
		map<T, unsigned int> size;
		map<T, T> parent;
	
		void combine(T set1, T set2)
		{
			parent[set1] = set2;
			size[set1] += size[set2];
		}

	public:
		bool exists(T elem)
		{
			return parent.find(elem) != parent.end();
		}
		
		void create(T elem)
		{
			if(!exists(elem))
			{
				parent[elem] = elem;
				size[elem] = 1;
			}
		}

		void join(T elem1, T elem2)
		{
			T elem1_set = find(elem1);
			T elem2_set = find(elem2);
			
			if(elem1_set != elem2_set)
			{
				if(size[elem1_set] < size[elem2_set])
				{
					combine(elem1_set, elem2_set);
				}
				else
				{
					combine(elem2_set, elem1_set);
				}
			}
		}		
	
		bool connected(T elem1, T elem2)
		{
			return find(elem1) == find(elem2);
		}
	
		T find(int elem)
		{
			return (parent[elem] = (parent[elem] == elem? elem: find(parent[elem])));
		}

		friend ostream& operator<<(ostream &out, DisjointSet<T> &s)
		{
			for(typename map<T, T>::iterator itr = s.parent.begin(); itr != s.parent.end(); itr++)
			{
				out << itr->first << " ------> " << itr->second << endl;
			}
		}
};

#endif
