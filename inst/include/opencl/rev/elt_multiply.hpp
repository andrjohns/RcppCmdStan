#ifndef STAN_MATH_OPENCL_REV_ELT_MULTIPLY_HPP
#define STAN_MATH_OPENCL_REV_ELT_MULTIPLY_HPP
#ifdef STAN_OPENCL

#include <opencl/rev/adjoint_results.hpp>
#include <opencl/matrix_cl.hpp>
#include <opencl/kernel_generator.hpp>
#include <opencl/prim/sum.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/rev/fun/value_of.hpp>
#include <stan/math/rev/core/reverse_pass_callback.hpp>
#include <stan/math/prim/fun/value_of.hpp>
#include <stan/math/prim/meta/is_kernel_expression.hpp>

namespace stan {
namespace math {

/**
 * Elementwise multiplication of two reverse mode matrices and/or kernel
 * generator expressions.
 * @tparam T_a type of first expression
 * @tparam T_b type of second expression
 * @param a first expression
 * @param b second expression
 * @return Elementwise multiplication of the input arguments
 */
template <
    typename T_a, typename T_b,
    require_all_nonscalar_prim_or_rev_kernel_expression_t<T_a, T_b>* = nullptr,
    require_any_var_t<T_a, T_b>* = nullptr>
inline var_value<matrix_cl<double>> elt_multiply(T_a&& a, T_b&& b) {
  arena_t<T_a> a_arena = std::forward<T_a>(a);
  arena_t<T_b> b_arena = std::forward<T_b>(b);

  return make_callback_var(
      elt_multiply(value_of(a_arena), value_of(b_arena)),
      [a_arena, b_arena](const vari_value<matrix_cl<double>>& res) mutable {
        adjoint_results(a_arena, b_arena)
            += expressions(elt_multiply(res.adj(), value_of(b_arena)),
                           elt_multiply(res.adj(), value_of(a_arena)));
      });
}

}  // namespace math
}  // namespace stan

#endif
#endif
