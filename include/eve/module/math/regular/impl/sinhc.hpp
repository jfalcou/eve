//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <eve/module/math/regular/sinh.hpp>

namespace eve::detail
{

  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr auto
  sinhc_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return one(eve::as(a0));
        if constexpr( eve::platform::supports_infinites )
          if( is_infinite(a0) ) return zero(eve::as<T>());
        if constexpr( eve::platform::supports_denormals )
          return eve::abs(a0) < eps(as<T>()) ? one(eve::as<T>()) : sinh(a0) / a0;
        else return sinh(a0) / a0;
      }
      else
      {
        auto sinhc_kernel = [](auto x2)
          {
            using elt_t = element_type_t<T>;
            if constexpr( std::is_same_v<elt_t, float> )
            {
              return
                eve::reverse_horner(x2, T(0x1.000000p+0f), T(0x1.555598p-3f)
                                   , T(0x1.10f77cp-7f), T(0x1.ab3c5ep-13f))
                ;
            }
            else
            {
              return inc(x2 * eve::reverse_horner(x2, T(-0x1.5782bdbf6ab05p+18), T(-0x1.694b8c71d6182p+13)
                                                 , T(-0x1.4773a398ff4fep+7), T(-0x1.9435fe8bb3cd6p-1))
                         /
                         eve::reverse_horner(x2, T(-0x1.01a20e4f90044p+21), T(0x1.1a7ba7ed72245p+15)
                                            , T(-0x1.15b6096e96484p+8), T(0x1.0p0))
                        );
            }
          };

        T    x   = abs(a0);
        auto lt1 = is_less(x, one(eve::as<T>()));
        auto nb  = eve::count_true(lt1);
        T    z   = zero(eve::as<T>());
        if( nb > 0 )
        {
          z = sinhc_kernel(sqr(x));
          if( nb >= T::size() ) return z;
        }
        auto test1 = is_greater(x, maxlog(eve::as<T>()) - log_2(eve::as<T>()));
        T    fac   = if_else(test1, half(eve::as<T>()), one(eve::as<T>()));
        T    tmp   = exp(x * fac);
        T    tmp1  = (half(eve::as<T>()) * tmp) / x;
        T    r     = if_else(test1, tmp1 * tmp, average(tmp, -rec(tmp)) / x);
        if constexpr( eve::platform::supports_infinites ) r = if_else(x == inf(eve::as<T>()), x, r);
        return if_else(lt1, z, r);
      }
    }
    else { return apply_over(sinhc, a0); }
  }

// -----------------------------------------------------------------------------------------------
// Masked cases
  template<conditional_expr C, value U>
  EVE_FORCEINLINE auto
  sinhc_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
  {
    return mask_op(cond, eve::sinhc, t);
  }

  template<conditional_expr C, decorator D, value U>
  EVE_FORCEINLINE auto
  sinhc_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
  {
    return mask_op(cond, d(eve::sinhc), t);
  }
}
