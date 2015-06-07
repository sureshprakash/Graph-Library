#ifndef _DISJOINT_SET
#define _DISJOINT_SET

#include <iostream>

using namespace std;

class DisjointSet  // Weighted quick union + Path compression
{
	private:
	int *id, *count, size;
	
	void combine_with(int a, int b)
	{
		id[a] = b;
		count[b] += count[a];
	}
	
	public:
	DisjointSet(int N)
	{
		size = N;
		id = new int[size];
		count = new int[size];
		
		initialize();
	}
	
	void initialize()
	{
		for(int i = 0; i < size; i++)
		{
			id[i] = i;
			count[i] = 1; // Initially there will be one node in the tree
		}
	}
	
	void join(int a, int b)
	{
		int a_root = root(a);
		int b_root = root(b);
		
		if(count[a_root] < count[b_root])
			combine_with(a_root, b_root);
		else
			combine_with(b_root, a_root);
	}
	
	bool connected(int a, int b)
	{
		return root(a) == root(b);
	}
	
	int root(int num)
	{
		id[num] = id[id[num]]; // Path compression statement
		return (num == id[num])? num: root(id[num]);
	}
	
	void display()
	{	
		for(int i = 0; i < size; i++)
			cout << id[i] << " ";
			
		cout << endl;
		
		for(int i = 0; i < size; i++)
			cout << count[i] << " ";
	}
	
	~DisjointSet()
	{
		delete count;
		delete id;
	}
};

#endif
