[![Build Status](https://travis-ci.com/kharchenkolab/sccore.svg?branch=master)](https://travis-ci.com/kharchenkolab/sccore)

# N2R
R extensions to N2 implementing kNN functions. 

Related libraries:
* The original C++ library with Python and Go bindings here: https://github.com/kakao/n2 
* Rust library here: https://github.com/rust-cv/hnsw


## Functions

* `n2Knn()`: k-NN using N2 approximate nearest neighbors algorithm

* `n2CrossKnn()`: matrixA cross matrixB k-NN using N2 



## Installation

For Mac OS X 10.15.5, 

`brew install gcc gfortran`

I've included `llvm` as well for my configuration below, though it's not required.

including the following in my `~/.zshrc`:

```
export PATH="/usr/local/opt/llvm/bin:$PATH"
export LDFLAGS="-L/usr/local/opt/llvm/lib"
export CPPFLAGS="-I/usr/local/opt/llvm/include"
```

and my `.R/Makevars` contains:

```
XCBASE:=$(shell xcrun --show-sdk-path)
LLVMBASE:=$(shell brew --prefix llvm)
GCCBASE:=$(shell brew --prefix gcc)
GETTEXT:=$(shell brew --prefix gettext)

CC=$(LLVMBASE)/bin/clang -fopenmp
CXX=$(LLVMBASE)/bin/clang++ -fopenmp
CXX11=$(LLVMBASE)/bin/clang++ -fopenmp
CXX14=$(LLVMBASE)/bin/clang++ -fopenmp
CXX17=$(LLVMBASE)/bin/clang++ -fopenmp
CXX1X=$(LLVMBASE)/bin/clang++ -fopenmp

CPPFLAGS=-isystem "$(LLVMBASE)/include" -isysroot "$(XCBASE)"
LDFLAGS=-L"$(LLVMBASE)/lib" -L"$(GETTEXT)/lib" --sysroot="$(XCBASE)"

FC=$(GCCBASE)/bin/gfortran -fopenmp
F77=$(GCCBASE)/bin/gfortran -fopenmp
FLIBS=-L$(GCCBASE)/lib/gcc/9/ -lm
```
