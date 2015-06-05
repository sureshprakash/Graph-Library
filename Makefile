all:
	g++ graph_test.cpp -o graph -g
	./graph
	
clean:
	rm -rf graph directed
	find . -name '*~' -delete
	
test_directed:
	g++ directed_graph_unit_test.cpp -o directed -g
	./directed
