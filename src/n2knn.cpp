// [[Rcpp::depends(RcppEigen)]]

#include <RcppEigen.h>
#include <queue>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>

#include "n2/hnsw.h"

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;

typedef Eigen::Triplet<double> T;

using namespace std;
using namespace Rcpp;

#define INDEX_TYPE_COSINE 2
#define INDEX_TYPE_LP 3

//' Perform fast approximate K-nearest neighbor search on input matrix. Algorithm based 
//' on N2 implmenetation of an approximate nearest neighbor search using Hierarchical NSW graphs. 
//' The original algorithm is described in "Efficient and Robust Approximate Nearest Neighbor 
//' Search Using Hierarchical Navigable Small World Graphs", Y. Malkov and D. Yashunin, doi: 10.1109/TPAMI.2018.2889473
//'
//' @param m Input numeric matrix of data 
//' @param k Integer number of clusters
//' @param nThreads Integer number of threads (default=10)
//' @param verbose Boolean flag for verbose output (default=FALSE)
//' @param indexType Metric distance type, which can be "angular" or "L2" (default="angular")
//' @param M integer (default=12)
//' @param MaxM0 integer (default=24)
//' @param ef_search_multiplier numeric (default=50)
//' @param quiet Boolean flag specifically for Rcpp warnings (default=FALSE)
//' @export
// [[Rcpp::export]]
Eigen::SparseMatrix<double> n2Knn(const NumericMatrix& m, int k, int nThreads=10, bool verbose=true, std::string indexType="angular", int M=12, int MaxM0=24, float ef_search_multiplier=50, bool quiet=false) {
  Eigen::SparseMatrix<double> mat(m.nrow(),m.nrow());

  if(m.nrow() <= k) {
    if (!quiet) {
      Rcpp::warning("k >= m.nrow(), reducing it to m.nrow() - 1");
    }

    k = m.nrow() - 1;
  }

  if(verbose) cout<<"creating space of type "<<indexType<<" done\n";
  n2::Hnsw index(m.ncol(), indexType);
  if(verbose) cout<<"adding data ... "<<flush;
  for(int i=0;i<m.nrow();i++) {
    NumericVector nv = m.row(i);
    std::vector<float> v(nv.begin(),nv.end());
    index.AddData(v);
  }
  if(verbose) cout<<"done"<<endl;

  if(verbose) cout<<"building index ... "<<flush;
  index.Build(M, MaxM0, -1, nThreads);
  if(verbose) cout<<"done"<<endl;

  int ef_search = k*ef_search_multiplier;

  int nanswers=k*m.nrow();

  if(verbose) cout<<"querying ... "<<flush;

  //#pragma omp parallel for num_threads(nThreads) shared(index,ansloc,ansdist,m,ef_search,nanswers)
  std::vector<T> tripletList;
  tripletList.reserve(nanswers);

  for(int i=0;i<m.nrow();i++) {
    std::vector<std::pair<int, float> > result;
    index.SearchById(i, k, ef_search, result);
    int nr=result.size();
    if(nr>k) nr=k;
    for(int j=0;j<nr;j++) {
      int l=i*k+j;
      //cout<<"i="<<i<<"; j="<<j<<"; n="<<result[j].first<<"; d="<<result[j].second<<endl;
      tripletList.push_back(T(result[j].first,i,result[j].second));
    }
  }
  if(verbose) cout<<"done"<<endl;

  mat.setFromTriplets(tripletList.begin(),tripletList.end());
  return(mat);
};


//' find NN of A in B
//'
//' @param mA matrix i.e. Rcpp::NumericMatrix
//' @param mB matrix i.e. Rcpp::NumericMatrix
//' @param k Integer number of clusters
//' @param nThreads Integer number of threads (default=10)
//' @param verbose Boolean flag for verbose output (default=FALSE)
//' @param indexType Metric distance type, which can be "angular" or "L2" (default="angular")
//' @param M integer (default=12)
//' @param MaxM0 integer (default=24)
//' @param ef_search_multiplier numeric (default=50)
//' @param quiet Boolean flag specifically for Rcpp warnings (default=FALSE)
//' @export
// [[Rcpp::export]]
Eigen::SparseMatrix<double> n2CrossKnn(const NumericMatrix& mA, const NumericMatrix& mB, int k, int nThreads=10, bool verbose=true, std::string indexType="angular", int M=12, int MaxM0=24, float ef_search_multiplier=50, bool quiet=false) {

  Eigen::SparseMatrix<double> mat(mB.nrow(),mA.nrow());

  if(mB.nrow() <= k) {
    if (!quiet) {
      Rcpp::warning("k >= mB.nrow(), reducing it to mB.nrow() - 1");
    }

    k = mB.nrow() - 1;
  }

  if(verbose) cout<<"creating space of type "<<indexType<<" done\n";
  n2::Hnsw index(mB.ncol(), indexType);
  if(verbose) cout<<"adding data ... "<<flush;
  for(int i=0;i<mB.nrow();i++) {
    NumericVector nv = mB.row(i);
    std::vector<float> v(nv.begin(),nv.end());
    index.AddData(v);
  }
  if(verbose) cout<<"done"<<endl;

  if(verbose) cout<<"building index ... "<<flush;
  index.Build(M, MaxM0, -1, nThreads);
  if(verbose) cout<<"done"<<endl;

  int ef_search = k*ef_search_multiplier;

  int nanswers=k*mA.nrow();
  std::vector<T> tripletList;
  tripletList.reserve(nanswers);

  if(verbose) cout<<"querying ... "<<flush;

  for(int i=0;i<mA.nrow();i++) {
    NumericVector nv = mA.row(i);
    std::vector<float> v(nv.begin(),nv.end());
    std::vector<std::pair<int, float> > result;
    index.SearchByVector(v, k, ef_search, result);
    int nr=result.size();
    if(nr>k) nr=k;
    for(int j=0;j<nr;j++) {
      int l=i*k+j;
      tripletList.push_back(T(result[j].first,i,result[j].second));
    }
  }
  if(verbose) cout<<"done"<<endl;

  mat.setFromTriplets(tripletList.begin(),tripletList.end());
  return(mat);
};


