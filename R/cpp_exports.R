call_stan <- function(options_vector, num_threads = 1) {
  sinkfile <- tempfile()
  sink(file = file(sinkfile, open = "wt"), type = "message")
  Sys.setenv(STAN_NUM_THREADS = num_threads)
  status <- .Call(`_cmdstan_main`, options_vector)
  sink(file = NULL, type = "message")
  sinklines <- paste(readLines(sinkfile), collapse = "\n")
  if ((status == 0) && (sinklines != "")) {
    stop(sinklines, call. = FALSE)
  }
  invisible(NULL)
}
