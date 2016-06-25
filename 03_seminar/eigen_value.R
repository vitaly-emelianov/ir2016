gen_matrix_impl <- function(n) {
  return (matrix(data = rnorm(n = n * n),
                 nrow = n,
                 ncol = n))
}

gen_matrix <- function(n) {
  m <- gen_matrix_impl(n)
  return (m %*% t(m))
}

len <- function(v) {
  return (sqrt(sum(v * v)))
}

norm <- function(v) {
  return (v / len(v))
}

get_spectrum <- function(m, iter = 100) {
  v <- norm(rnorm(n = nrow(m)))
  a <- 1
  n = nrow(m)
  eigenvalues = c()
  eigenvectors = list()
  
  for (j in 1:n) {
    for (i in 1:iter) {
      new_v <- v %*% m
      a <- len(new_v)
      v <- norm(new_v)
    }
    eigenvalues <- c(eigenvalues, a)
    eigenvectors[[length(eigenvectors) + 1]] <- v
    m = m - a * matrix(v) %*% t(matrix(v))
  }
  return (list("eigenvalues"=eigenvalues, 
               "eigenvectors"=eigenvectors, 
               "error"=eigen(m)$values[1]))
}

make_experiment <- function(matrix_number = 15) {
  avg_errors <- c()
  for (n in 10:100) {
    cat(round((n - 10) / 91 * 100, digits = 2), " %\n")
    errors <- c()
    for (i in 1:matrix_number) {
      m <- gen_matrix(n)
      ans = get_spectrum(m)
      errors <- c(errors, ans$error)
    }
    avg_errors <- c(avg_errors, mean(errors))
  }
  plot(10:100, avg_errors, xlab = "Matrix Size", ylab = "Average Error")
}

make_experiment()

