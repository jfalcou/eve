//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_not_less_equal.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/oneminus.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve::detail
{
  template<callable_options O, typename T>
  EVE_FORCEINLINE constexpr T floor_(EVE_REQUIRES(cpu_), O const& o, T const& v) noexcept
  {
    if constexpr (integral_value<T>) return v;
    else
    {
      if constexpr (O::contains(almost))
      {
        auto tol = o[almost].value(v);
        if constexpr (integral_value<decltype(tol)>)
          return floor(next(v, tol));
        else
        {
          // Hagerty's FL5 function
          auto q    = if_else(is_ltz(v), one, oneminus(tol));
          auto rmax = q / (T{2} - tol);
          auto tol5 = tol / q;
          auto r    = floor(v + eve::max(tol, min(rmax, tol5 * eve::abs(inc(floor(v))))));
          return if_else(is_lez(v) || (r - v < rmax), r, dec(r));
        }
      }
      else
      {
        // if constexpr (floating_scalar_value<T>)
        // {
        //   if (is_not_finite(v)) return v;
        // }

        using elt_t = element_type_t<T>;
        using i_t   = as_integer_t<elt_t>;
        // auto z = convert(convert(v, as<i_t>{}), as<elt_t>{});

        // auto already_integral = is_not_less_equal(eve::abs(v), maxflint(as<T>{}));

        //      if constexpr (scalar_value<T>) z = already_integral ? v : z;
        // else if constexpr (simd_value<T>)   z = if_else(already_integral, v, z);

        // return dec[z > v](z);

        auto nf = is_not_finite(v);

        if constexpr (scalar_value<T>)
        {
          if (nf) return v;
          else
          {
            auto z = convert(convert(v, as<i_t>{}), as<elt_t>{});
            auto already_integral = is_not_less_equal(eve::abs(v), maxflint(as<T>{}));
            z = already_integral ? v : z;
            return dec[z > v](z);
          }
        }
        else
        {
          auto vnf = if_else(nf, zero, v);
          auto z = convert(convert(vnf, as<i_t>{}), as<elt_t>{});
          auto already_integral = is_not_less_equal(eve::abs(vnf), maxflint(as<T>{}));
          z = if_else(already_integral, vnf, z);
          return dec[z > vnf](z);
        }
      }
    }
  }

  template<callable_options O, typename T, typename U>
  EVE_FORCEINLINE constexpr auto floor_(EVE_REQUIRES(cpu_), O const&, T const& v, as<U>) noexcept
  {
    if constexpr(integral_value<T>) return convert(v, as_element<as_integer_t<T,U>>{});
    else                            return convert(floor(v), as_element<as_integer_t<T,U>>{});
  }
}
