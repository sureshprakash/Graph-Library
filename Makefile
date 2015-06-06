all:
	g++ graph_test.cpp -o graph -g
	./graph
	
clean:
	rm -rf graph directed weighted
	find . -name '*~' -delete
	
test_directed:
	g++ directed_graph_unit_test.cpp -o directed -g
	./directed
	
test_weighted:
	g++ directed_weighted_graph_unit_test.cpp -o weighted -g
	./weighted
	
git: clean
	git add *
	git commit -a
