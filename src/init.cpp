#include <Rcpp.h>
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>
#include <Rversion.h>

using namespace Rcpp;

#ifdef __cplusplus
extern "C"  {
#endif

SEXP _cmdstan_main(SEXP options_vector);

#ifdef __cplusplus
}
#endif


#define CALLDEF(name, n)  {#name, (DL_FUNC) &name, n}

static const R_CallMethodDef CallEntries[] = {
  CALLDEF(_cmdstan_main, 1),
  {NULL, NULL, 0}
};

#ifdef __cplusplus
extern "C"  {
#endif
void attribute_visible R_init_RcppCmdStan(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
#ifdef __cplusplus
}
#endif
