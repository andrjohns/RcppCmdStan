#ifndef STAN_MATH_OPENCL_REV_LOG_DIFF_EXP_HPP
#define STAN_MATH_OPENCL_REV_LOG_DIFF_EXP_HPP
#ifdef STAN_OPENCL

#include <opencl/rev/adjoint_results.hpp>
#include <opencl/matrix_cl.hpp>
#include <opencl/kernel_generator.hpp>
#include <opencl/prim/sum.hpp>
#include <stan/math/rev/core.hpp>
#include <stan/math/rev/fun/adjoint_of.hpp>
#include <stan/math/rev/fun/value_of.hpp>
#include <stan/math/rev/core/reverse_pass_callback.hpp>
#include <stan/math/prim/fun/value_of.hpp>
#include <stan/math/prim/meta/is_kernel_expression.hpp>

namespace stan {
namespace math {

/**
 * Returns  the natural logarithm of the difference
 * of the natural exponentiation of x and
 * the natural exponentiation of y.
 *
 * @tparam T_x type of x argument
 * @tparam T_y type of y argument
 * @param x first argument
 * @param y second argument
 * @return Result the natural logarithm of the difference
 * of the natural exponentiation of x and
 * the natural exponentiation of y.
 */
template <typename T_x, typename T_y,
          require_all_prim_or_rev_kernel_expression_t<T_x, T_y>* = nullptr,
          require_any_var_t<T_x, T_y>* = nullptr,
          require_any_not_stan_scalar_t<T_x, T_y>* = nullptr>
inline var_value<matrix_cl<double>> log_diff_exp(T_x&& x, T_y&& y) {
  arena_t<T_x> x_arena = std::forward<T_x>(x);
  arena_t<T_y> y_arena = std::forward<T_y>(y);

  return make_callback_var(
      log_diff_exp(value_of(x_arena), value_of(y_arena)),
      [x_arena, y_arena](const vari_value<matrix_cl<double>>& res) mutable {
        adjoint_results(x_arena, y_arena) += expressions(
            -elt_divide(res.adj(),
                        expm1(value_of(y_arena) - value_of(x_arena))),
            -elt_divide(res.adj(),
                        expm1(value_of(x_arena) - value_of(y_arena))));
      });
}

}  // namespace math
}  // namespace stan

#endif
#endif
