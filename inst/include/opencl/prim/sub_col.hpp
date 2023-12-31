#ifndef STAN_MATH_OPENCL_PRIM_SUB_COL_HPP
#define STAN_MATH_OPENCL_PRIM_SUB_COL_HPP
#ifdef STAN_OPENCL

#include <opencl/matrix_cl.hpp>
#include <opencl/prim/block.hpp>

namespace stan {
namespace math {

/**
 * Return a 1 x ncols subrow starting at (i-1, j-1).
 *
 * @tparam T_x type of input kernel generator expression x
 * @param x input kernel generator expression.
 * @param i Starting row + 1.
 * @param j Starting column + 1.
 * @param nrows Number of rows in block.
 * @throw std::out_of_range if either index is out of range.
 */
template <typename T_x,
          typename = require_nonscalar_prim_or_rev_kernel_expression_t<T_x>>
inline auto sub_col(T_x&& x, size_t i, size_t j, size_t nrows) {
  return block(std::forward<T_x>(x), i, j, nrows, 1);
}
}  // namespace math
}  // namespace stan
#endif
#endif
