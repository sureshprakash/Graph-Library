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
			size[set2] += size[set1];
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

		map<T, unsigned int> getSetsWithSize()
		{
			map<T, unsigned int> res;

			for(typename map<T, unsigned int>::iterator itr = size.begin(); itr != size.end(); itr++)
			{
				if(parent[itr->first] == itr->first)	// Root of the set
				{
					res[itr->first] = itr->second;
				}
			}

			return res;
		}

		unsigned int numSets()
		{
			unsigned int cnt = 0;

			for(typename map<T, unsigned int>::iterator itr = size.begin(); itr != size.end(); itr++)
			{
				if(parent[itr->first] == itr->first)	// Root of the set
				{
					cnt++;
				}
			}

			return cnt;
		}

		friend ostream& operator<<(ostream &out, DisjointSet<T> &s)
		{
			for(typename map<T, T>::iterator itr = s.parent.begin(); itr != s.parent.end(); itr++)
			{
				out << itr->first << " ------> " << itr->second << endl;
			}
            
            out << "Sets: " << endl;
            map<T, unsigned int> sets = s.getSetsWithSize();
            for(typename map<T, unsigned int>::iterator itr = sets.begin(); itr != sets.end(); itr++)
            {
                out << "|" << itr->first << "| = " << itr->second << endl;
            }

			return out;
		}
};

#endif
