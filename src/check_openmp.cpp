// [[Rcpp::plugins(openmp)]]
#include <Rcpp.h>

using namespace Rcpp;

//' boolean to check OpenMP exists
//' 
// [[Rcpp::export]]
bool checkOpenMP() {
#ifdef _OPENMP
	return true;
#else
	return false;
#endif
}