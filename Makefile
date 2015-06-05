all:
	g++ graph_test.cpp -o graph -g
	./graph
	
clean:
	rm -rf graph
	find . -name '*~' -delete
