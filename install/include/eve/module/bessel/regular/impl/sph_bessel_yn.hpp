//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/bessel/regular/cyl_bessel_yn.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
template<value I, floating_value T>
EVE_FORCEINLINE auto
sph_bessel_yn_(EVE_SUPPORTS(cpu_), I n, T x) noexcept
{
  EVE_ASSERT(all(is_gez(n) && is_flint(n)),
             "sph_bessel_yn : some orders are non integral positive");
  EVE_ASSERT(all(is_nltz(x)), "sph_bessel_yn : some x are negative");
  using elt_t = element_type_t<T>;
  if constexpr( integral_value<I> ) return sph_bessel_yn(convert(n, as<elt_t>()), x);
  else return cyl_bessel_yn(n + half(as(x)), x) * rsqrt(2 * x * inv_pi(as(x)));
}
}
