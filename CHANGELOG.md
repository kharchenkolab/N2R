# Changelog

## [1.0.5] - 2026-March-29
* Try to update the n2 C++ source code, last commit 20b02de8bdcf808312232dd4784c2902476063da
June 28 2023, PR #52 from 
* Fix misaligned pointer warning from gcc-UBSAN on CRAN with std::memcpy() for SetValueAndIncPtr() and GetValueAndIncPtr()
* Guard headers with conditionals for Linux/Mac and Windows, i.e. former and latters uses VirtualAlloc() and VirtualFree(), and the 
* Remove `std::bind1st()`` from /include/n2/utils.h, use lambda instead 
* Replace `_mm_prefetch()` as xmmintrin.h header doesn't work on ARM64; use `__builtin_prefetch()` instead
* Fix "unqualified call" warning, use `std::move()`
* Explicitly set `int tid = 1;` instead of `int tid = omp_get_thread_num();`
* To fix gcc-UBSan error, remove data type in chevrons for `SetValueAndIncPtr()`


## [1.0.4] - 2026-March-05
* Reformat the arXiv DOI for CRAN
* Remove 'Rcpp:::LdFlags()' as no longer needed based on CRAN 

## [1.0.3] - 2024-Feb-26
* Need to explicitly set `CXX ?= g++` as some default clang settings need explicit '-std=c++11'

## [1.0.2] - 2024-Feb-22
* Remove 'SystemRequirements: C++11, GNU make'
* Fix Makevars files

## [1.0.1] - 2022-01-08
* Explicitly use 'SystemRequirements: C++11'
* Fix SIMD intrinsics for package compiles with Macbook M1, cf https://github.com/oddconcepts/n2o/commit/fe6214dcc06a1b13be60733c53ac25bca3c2b4d0

## [1.0.0] - 2021-11-19
* `N2R` has gone through no major revisions in over a year. In order to avoid any confusion, this should be released with a major version.

## [0.1.1] - September 30 2020
