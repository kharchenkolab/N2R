
library(N2R)
library(testthat)

data(iris)
irisdf = data.matrix(iris[-5])
set.seed(42123)

test_that("basic Knn() functionality", {
	expect_equal(dim(Knn(irisdf, 4))[1], 150)
	expect_equal(dim(Knn(irisdf, 4))[2], 150)
})

test_that("basic corssKnn() functionality", {
	expect_equal(dim(crossKnn(irisdf, head(irisdf, 100), 4))[1], 100)
	expect_equal(dim(crossKnn(irisdf, head(irisdf, 100), 4))[2], 150)
})

test_that("Knn indexType accepts only angular, L2", {
	expect_error(Knn(irisdf, 4, indexType="foobar"))
})

test_that("crossKnn indexType accepts only angular, L2", {
	expect_error(crossKnn(irisdf, head(irisdf, 100), 4, indexType="foobar"))
})

