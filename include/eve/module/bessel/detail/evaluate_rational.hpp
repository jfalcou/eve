//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{
  template <class T, class U, class V>
  EVE_FORCEINLINE V evaluate_rational(const T num, const U den, V z) noexcept
  {
    auto eval_small = [&num, &den](auto z)
      {
        return reverse_horner(z, num)/reverse_horner(z, den);
      };
    auto eval_large = [&num, &den](auto z)
      {
        z = rec(z);
        auto r =  horner(z, num)/horner(z, den);
        if(size(den) == size(num))
          return r;
        else
          return r*pow(z, size(num)-size(den));
      };
    auto test = z <= V(1);
    if(eve::all(test)) return eval_small(z);
    else if(eve::all(z >= V(1))) return  eval_large(z);
    else return if_else(test,  eval_small(z),  eval_large(z));
  }

  template <class T, class U, class V>
  EVE_FORCEINLINE V reverse_evaluate_rational(const T num, const U den, V z) noexcept
  {
    auto eval_small = [&num, &den](auto z)
      {
        return horner(z, num)/horner(z, den);
      };
    auto eval_large = [&num, &den](auto z)
      {
        z = rec(z);
        auto r = reverse_horner(z, num)/reverse_horner(z, den);
        if(size(den) == size(num))
          return r;
        else
          return r*pow(z, size(num)-size(den));
     };
    auto test = z <= V(1);
    if(eve::all(test)) return eval_small(z);
    else if(eve::all(z >= V(1))) return  eval_large(z);
    else return if_else(test,  eval_small(z),  eval_large(z));
  }
//   template <class T, class U, class V>
//   EVE_FORCEINLINE V evaluate_rational(const T num, const U den, V z) noexcept
//   {
//     auto N =  num.size();
//     auto eval_small = [&num, &den, N](auto z)
//       {
//         V s1(num[N-1]);
//         V s2(den[N-1]);
//         for(int i = (int)N - 2; i >= 0; --i)
//         {
//           s1 = fma(s1, z, num[i]);
//           s2 = fma(s2, z, den[i]);
//         }
//         return s1/s2;
//       };
//     auto eval_large = [&num, &den, N](auto z)
//       {
//         z = rec(z);
//         V s1(num[0]);
//         V s2(den[0]);
//         for(unsigned i = 1; i < N; ++i)
//         {
//           s1 = fma(s1, z, num[i]);
//           s2 = fma(s2, z, den[i]);
//         }
//         return s1/s2;
//        };
//     auto test = z <= V(1);
//     if(eve::all(test)) return eval_small(z);
//     else if(eve::none(test)) return  eval_large(z);
//     else return if_else(test,  eval_small(z),  eval_large(z));
//   }
}
