#ifndef STAN_MATH_OPENCL_REV_VARIANCE_HPP
#define STAN_MATH_OPENCL_REV_VARIANCE_HPP
#ifdef STAN_OPENCL

#include <opencl/rev/arena_matrix_cl.hpp>
#include <opencl/kernel_generator.hpp>
#include <opencl/prim/mean.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/rev/fun/value_of.hpp>

namespace stan {
namespace math {

/**
 * Return the sample variance of the var_value matrix
 * Raise domain error if size is not greater than zero.
 *
 * @tparam Mat input matrix type
 * @param A input
 * @return sample variance of the input
 */
template <typename T,
          require_all_kernel_expressions_and_none_scalar_t<T>* = nullptr>
inline var variance(const var_value<T>& A) {
  if (A.size() == 1) {
    return 0.0;
  }
  double A_mean = mean(A.val());
  arena_matrix_cl<double> diff;
  matrix_cl<double> sq_norm;
  auto diff_expr = A.val() - A_mean;
  auto sq_norm_expr = sum_2d(square(diff));
  results(diff, sq_norm) = expressions(diff_expr, sq_norm_expr);

  return make_callback_var(
      elt_divide(from_matrix_cl(sq_norm).sum(), A.size() - 1.0),
      [A, diff](vari& res) mutable {
        A.adj() += elt_divide(2.0 * res.adj(), A.size() - 1.0) * diff;
      });
}

}  // namespace math
}  // namespace stan

#endif
#endif
