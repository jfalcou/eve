//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <vector>


namespace eve::detail
{
// (-1)^m d^m/dz^m cot(z) = p_m(cot z), where p_m is a polynomial
// that satisfies the recurrence p_{m+1}(x) = p_m′(x) * (1 + x^2).
// Note that p_m(x) has only even powers of x if m is odd, and
// only odd powers of x if m is even.  Therefore, we write p_m(x)
// as p_m(x) = q_m(x^2) m! for m odd and p_m(x) = x q_m(x^2) m! if m is even.
// Hence the polynomials q_m(y) satisfy the recurrence:
//     m odd:  q_{m+1}(y) = 2 q_m′(y) * (1+y) / (m+1)
//    m even:  q_{m+1}(y) = [q_m(y) + 2 y q_m′(y)] * (1+y) / (m+1)
// This function computes the coefficients of the polynomial q_m(y),
// returning an array of the coefficients of 1, y, y^2, ...,
  auto cotderiv(std::size_t m)
  {
    if (m == 0)  return std::vector<double>{1.0};
    if (m == 1 || m == 2)   return std::vector<double>{1.0, 1.0};
      std::vector<double> qm = cotderiv(m-1);
      std::size_t d = qm.size() - 1; // degree of q
      if (eve::is_odd(m-1))
      {
        std::vector<double> q(qm.size());
        q[d] = (d) * qm[d] * 2.0/m;
        for(std::size_t i = 0; i < d; ++i)
          q[i] = (i*qm[i] + (i+1)*qm[i+1]) * 2.0/m;
        return q;
      }
      else // iseven(m-1)
      {
        std::vector<double> q(qm.size()+1);
        q[0] = qm[0] / m;
        q[d+1] = (1 + 2*d) * qm[d] / m;
        for (std::size_t i = 1; i <  d+1; ++i)
          q[i] = ((1 + 2*i)*qm[i] + (1 + 2*(i-1))*qm[i-1]) / m;
        return q;
      }

  }
}
