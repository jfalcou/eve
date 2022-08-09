//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/polynomial.hpp>

namespace eve::detail
{
template<class T, class U, class V>
EVE_FORCEINLINE V
evaluate_rational(const T num, const U den, V z) noexcept
{
  auto eval_small = [&num, &den](auto z)
  { return reverse_horner(z, num) / reverse_horner(z, den); };
  auto eval_large = [&num, &den](auto z)
  {
    z      = rec(z);
    auto r = horner(z, num) / horner(z, den);
    if( size(den) == size(num) ) return r;
    else return r * pow(z, size(num) - size(den));
  };
  auto test = z <= V(1);
  if( eve::all(test) ) return eval_small(z);
  else if( eve::all(z >= V(1)) ) return eval_large(z);
  else return if_else(test, eval_small(z), eval_large(z));
}

template<class T, class U, class V>
EVE_FORCEINLINE V
reverse_evaluate_rational(const T num, const U den, V z) noexcept
{
  auto eval_small = [&num, &den](auto z) { return horner(z, num) / horner(z, den); };
  auto eval_large = [&num, &den](auto z)
  {
    z      = rec(z);
    auto r = reverse_horner(z, num) / reverse_horner(z, den);
    if( size(den) == size(num) ) return r;
    else return r * pow(z, size(num) - size(den));
  };
  auto test = z <= V(1);
  if( eve::all(test) ) return eval_small(z);
  else if( eve::all(z >= V(1)) ) return eval_large(z);
  else return if_else(test, eval_small(z), eval_large(z));
}
}
