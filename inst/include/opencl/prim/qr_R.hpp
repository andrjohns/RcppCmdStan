#ifndef STAN_MATH_OPENCL_PRIM_QR_R_HPP
#define STAN_MATH_OPENCL_PRIM_QR_R_HPP
#ifdef STAN_OPENCL
#include <opencl/qr_decomposition.hpp>
#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/err.hpp>

namespace stan {
namespace math {

/**
 * Returns the orthogonal factor of the fat QR decomposition
 *
 * @tparam T_m type of the matrix
 * @param m Matrix.
 * @return Orthogonal matrix with maximal columns
 */
template <typename T_m,
          require_all_kernel_expressions_and_none_scalar_t<T_m>* = nullptr>
inline matrix_cl<double> qr_R(T_m&& m) {
  check_nonzero_size("qr_R(OpenCL)", "m", m);

  matrix_cl<double> mat_eval = std::forward<T_m>(m);
  matrix_cl<double> Q, R;

  qr_decomposition_cl<false>(m, Q, R);

  matrix_cl<double> R_diag = diagonal(R);
  auto R_top
      = block_zero_based(R, 0, 0, std::min(m.rows(), m.cols()), R.cols());
  R_top = select(rowwise_broadcast(R_diag < 0.0), -R_top, R_top);
  return R;
}
}  // namespace math
}  // namespace stan

#endif
#endif
