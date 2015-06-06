all:
	g++ graph_test.cpp -o graph -g
	./graph
	
clean:
	rm -rf graph directed weighted topsort bfs_dfs
	find . -name '*~' -delete
	
test_directed:
	g++ directed_graph_unit_test.cpp -o directed -g
	./directed
	
test_weighted:
	g++ directed_weighted_graph_unit_test.cpp -o weighted -g
	./weighted
	
test_topological:
	g++ topsort.cpp -o topsort -g
	./topsort
	
test_bfsdfs:
	g++ bfs_dfs.cpp -o bfs_dfs -g
	./bfs_dfs
	
git: clean
	git add *
	git commit -a
