all: hashtest splaytest

hashtest: hashtest.cpp hashtable.h
	g++ -g -Wall $< -o $@

splaytest: splaytest.cpp splaytree.h bst.h
	g++ -g -Wall $< -o $@

clean:
	rm splaytest hashtest