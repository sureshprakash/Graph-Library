all: test_directed test_weighted test_topological test_bfsdfs test_properties test_shortest_path test_components test_path test_mincut
	
clean:
	rm -rf graph directed weighted topsort bfs_dfs properties shortest_path components path mincut
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
	
test_properties:
	g++ graph_properties.cpp -o properties -g
	./properties
	
test_shortest_path:
	g++ shortest_path.cpp -o shortest_path -g
	./shortest_path
	
test_components:
	g++ components.cpp -o components -g
	./components
	
test_path:
	g++ path_test.cpp -o path -g
	./path
	
test_mincut:
	g++ mincut_test.cpp -o mincut -g
	./mincut
	
git: clean
	git add *
	git commit -a
