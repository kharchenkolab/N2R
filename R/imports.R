#' @useDynLib N2R
#' @import Rcpp
#' @import Matrix
NULL

#' Perform fast approximate K-nearest neighbor search on input matrix m.
#' 
#' @param m Input numeric matrix of data 
#' @param k Integer number of clusters
#' @param nThreads Integer number of threads (default=10)
#' @param verbose Boolean flag for verbose output (default=FALSE)
#' @param indexType Metric distance type, which can be "angular" or "L2" (default="angular")
#' @param M Integer number of connections (default=12) The NSW graph is constructed via consecutive insertion of elements in random order by bidirectionally connecting them to the M closest neighbors from the previously inserted elements.
#' @param MaxM0 Integer maximum number of connections that an element can have in the zero layer. (default=24) It is recommended that MaxM0 not exceed 2*M.
#' @param ef_search_multiplier Integer multiplier to calculate candidate nearest neighbors, set to k*ef_search_multiplier (default=50). Refer to the parameters er and efConstruction in Malkov & Yashunin (2020) doi: 10.1109/TPAMI.2018.2889473
#' @param quiet Boolean flag specifically for Rcpp warnings (default=FALSE)
#' @export
Knn = function(m, k, nThreads = 10L, verbose=TRUE, indexType="angular", M=12L, MaxM0=24L, ef_search_multiplier=50, quiet=FALSE){
	if (!is.character(indexType) || !(toupper(indexType) %in% c("ANGULAR", "L2")) ){
		stop("The metric distance indexType must be either 'L2' or 'angular'")
	}
	return(n2Knn(m=m, k=k, nThreads=nThreads, verbose=verbose, indexType=indexType, M=M, MaxM0=MaxM0, ef_search_multiplier=ef_search_multiplier, quiet=quiet))

}


#' Perform fast approximate K-nearest neighbor search of input matrix mA in matrix mB. 
#' 
#' @param mA Input numeric matrix of data 
#' @param mB Input numeric matrix of data
#' @param k Integer number of clusters
#' @param nThreads Integer number of threads (default=10)
#' @param verbose Boolean flag for verbose output (default=FALSE)
#' @param indexType Metric distance type, which can be "angular" or "L2" (default="angular")
#' @param M Integer number of connections (default=12) The NSW graph is constructed via consecutive insertion of elements in random order by bidirectionally connecting them to the M closest neighbors from the previously inserted elements.
#' @param MaxM0 Integer maximum number of connections that an element can have in the zero layer. (default=24) It is recommended that MaxM0 not exceed 2*M.
#' @param ef_search_multiplier Integer multiplier to calculate candidate nearest neighbors, set to k*ef_search_multiplier (default=50). Refer to the parameters er and efConstruction in Malkov & Yashunin (2020) doi: 10.1109/TPAMI.2018.2889473
#' @param quiet Boolean flag specifically for Rcpp warnings (default=FALSE)
#' @export
crossKnn = function(mA, mB, k, nThreads = 10L, verbose=TRUE, indexType="angular", M=12L, MaxM0=24L, ef_search_multiplier=50, quiet=FALSE){
	if (!is.character(indexType) || !(toupper(indexType) %in% c("ANGULAR", "L2")) ){
		stop("The metric distance indexType must be either 'L2' or 'angular'")
	}
	return(n2CrossKnn(mA=mA, mB=mB, k=k, nThreads=nThreads, verbose=verbose, indexType=indexType, M=M, MaxM0=MaxM0, ef_search_multiplier=ef_search_multiplier, quiet=quiet))
}