CXX ?= g++
PKG_CXXFLAGS = -O3 -pthread -fPIC -I"./include" $(SHLIB_OPENMP_CXXFLAGS) -DBOOST_DISABLE_ASSERTS
PKG_CXXFLAGS = -I"./include"
LDFLAGS = -lpthread

LIB = ../libn2.a
lib: $(LIB)

$(LIB): hnsw.o hnsw_build.o hnsw_search.o hnsw_model.o hnsw_node.o heuristic.o mmap.o
	ar rvs $@ $?

clean:
	@-rm -f *.o $(LIB) 