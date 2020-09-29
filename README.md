[![Build Status](https://travis-ci.com/kharchenkolab/N2R.svg?branch=master)](https://travis-ci.com/kharchenkolab/N2R)
[![CRAN status](https://www.r-pkg.org/badges/version/N2R)](https://cran.r-project.org/package=N2R)
[![CRAN downloads](https://cranlogs.r-pkg.org/badges/N2R)](https://cran.r-project.org/package=N2R)

# N2R
R extensions to N2 implementing kNN functions. 

Implements methods to perform fast approximate K-nearest neighbor search on input matrix. Algorithm based on N2 implementation of an approximate nearest neighbor search using Hierarchical NSW graphs. The original algorithm is described in "Efficient and Robust Approximate Nearest Neighbor Search Using Hierarchical Navigable Small World Graphs", Y. Malkov and D. Yashunin, doi: 10.1109/TPAMI.2018.2889473, arXiv: 1603.09320.

Related libraries:
* The original C++ library with Python and Go bindings here: https://github.com/kakao/n2 
* Rust library here: https://github.com/rust-cv/hnsw


## Installation

To install the stable version from CRAN, use:

```r
install.packages('N2R')
```

To install the latest version, use:

```r
install.packages('devtools')
devtools::install_github('kharchenkolab/N2R')
```

For installing from source on Mac OS, please see instructions in the wiki [here](https://github.com/kharchenkolab/N2R/wiki/Installing-N2R-for-Mac-OS)

## Functions

* `n2Knn()`: k-NN using N2 approximate nearest neighbors algorithm

* `n2CrossKnn()`: matrixA cross matrixB k-NN using N2 


## Citation

If you find `N2R` useful for your publication, please cite:

```
Peter Kharchenko, Viktor Petukhov and Evan Biederstedt (2020). N2R:
Fast and Scalable Approximate k-Nearest Neighbor Search Methods using
N2 Library. R package version 0.1.0.
https://github.com/kharchenkolab/N2R
```
