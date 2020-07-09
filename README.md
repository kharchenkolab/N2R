# N2R
R extensions to n2 implementing kNN functions, from conos

Newer version with Python and Go bindings here: https://github.com/kakao/n2
(Note: both Python and Go extensions are quite different in design than this library.)


## Functions

* `n2Knn()`: k-NN using n2 approximate nearest neighbors algorithm
(similar to )

* `n2CrossKnn()`: matrixA cross matrixB k-NN using n2 

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
