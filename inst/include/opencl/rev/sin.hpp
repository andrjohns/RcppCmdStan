#ifndef STAN_MATH_OPENCL_REV_SIN_HPP
#define STAN_MATH_OPENCL_REV_SIN_HPP
#ifdef STAN_OPENCL

#include <opencl/kernel_generator.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/rev/fun/value_of.hpp>

namespace stan {
namespace math {

/**
 * Returns the elementwise `cos()` of a var_value<matrix_cl<double>>
 * in radians.
 *
 * @param A argument
 * @return Elementwise `cos()` of the input, in radians.
 */
template <typename T,
          require_all_kernel_expressions_and_none_scalar_t<T>* = nullptr>
inline var_value<matrix_cl<double>> sin(const var_value<T>& A) {
  return make_callback_var(sin(A.val()),
                           [A](vari_value<matrix_cl<double>>& res) mutable {
                             A.adj() += elt_multiply(res.adj(), cos(A.val()));
                           });
}

}  // namespace math
}  // namespace stan

#endif
#endif
