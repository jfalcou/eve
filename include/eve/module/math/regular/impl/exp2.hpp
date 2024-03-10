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
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/constant/maxlog2.hpp>
#include <eve/module/math/constant/minlog2.hpp>
#include <eve/module/math/constant/minlog2denormal.hpp>

namespace eve::detail
{
  template<floating_ordered_value T, callable_options O, pedantic_type>
  EVE_FORCEINLINE constexpr T
  exp2_(EVE_SUPPORTS(cpu_), O const&, T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t    = element_type_t<T>;
      auto minlogval = []()
        {
          if constexpr(O::contains(pedantic2) && eve::platform::supports_denormals)
            return minlog2denormal(eve::as<T>());
          else
            return minlog2(eve::as<T>());
        };
      auto xltminlog2 = x <= minlogval();
      auto xgemaxlog2 = x >= maxlog2(eve::as(x));
      if constexpr( scalar_value<T> )
      {
        if( is_nan(x)  ) return nan(x);
        if( xgemaxlog2 ) return inf(eve::as(x));
        if( xltminlog2 ) return zero(eve::as(x));
      }
      auto k = nearest(x);
      x      = x - k;
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T y =
          eve::reverse_horner(x, T(0x1.ebfbe2p-3f), T(0x1.c6add6p-5f)
                             , T(0x1.3b2844p-7f), T(0x1.602430p-10f), T(0x1.459188p-13f));
        x   = inc(fma(y, sqr(x), x * log_2(eve::as<T>())));
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        x *= log_2(eve::as<T>());
        T    t = sqr(x);
        auto h =
          eve::reverse_horner(t, T(0x1.555555555553ep-3), T(-0x1.6c16c16bebd93p-9)
                             , T(0x1.1566aaf25de2cp-14), T(-0x1.bbd41c5d26bf1p-20), T(0x1.6376972bea4d0p-25));
        T    c = fnma(t, h, x); // x-h*t
        x      = oneminus(((-(x * c) / (T(2) - c)) - x));
      }
      auto z = ldexp[pedantic](x, k);
      if constexpr( simd_value<T> )
      {
        z = if_else(xltminlog2, eve::zero, z);
        z = if_else(xgemaxlog2, inf(eve::as(x)), z);
      }
      return z;
    }
    else { return apply_over(exp2[o], x); }
  }
}

// ////////////////////////////////////////////////////////////////////////////////////
// // integral types

//   template<integral_value T, typename D>
//   EVE_FORCEINLINE constexpr auto
//   exp2_(EVE_SUPPORTS(cpu_), D const&, T xx) noexcept
//   requires(is_one_of<D>(types<converter_type<float>,
//                         converter_type<double>,
//                         floating_converter,
//                         pedantic_type,
//                         raw_type,
//                         regular_type> {}))
// {
//   if constexpr( has_native_abi_v<T> )
//   {
//     if constexpr( is_one_of<D>(
//                     types<converter_type<float>, converter_type<double>, floating_converter> {}) )
//     {
//       using b_t  = std::conditional_t<std::is_same_v<D, floating_converter>,
//         eve::as_floating_point_t<T>,
//         typename D::base_type>;
//       using vd_t = typename b_t::value_type;
//       using i_t  = as_integer_t<vd_t>;

//       auto x  = to_<i_t>(xx);
//       auto z  = is_nez(x);
//       auto zz = eve::min(x + maxexponent(eve::as<vd_t>()), 2 * maxexponent(eve::as<vd_t>()) + 1)
//         & z.mask();
//       zz        = zz << nbmantissabits(eve::as<vd_t>());
//       using r_t = std::conditional_t<scalar_value<T>, vd_t, wide<vd_t, cardinal_t<T>>>;
//       return if_else(z, bit_cast(zz, as<r_t>()), one);
//     }
//     else
//     {
//       element_type_t<T> constexpr siz = sizeof(element_type_t<T>) * 8 - 1;
//       auto test                       = is_ltz(xx) || (xx > siz);
//       xx                              = if_else(test, zero, xx);
//       auto tmp                        = if_else(test, eve::zero, shl(one(eve::as(xx)), xx));
//       if constexpr( std::is_same_v<D, saturated_type> )
//       {
//         using elt_t = element_type_t<T>;
//         return if_else(is_gez(xx, T(sizeof(elt_t))), valmax(eve::as<T>()), tmp);
//       }
//       else return tmp;
//     }
//   }
//   else { return apply_over(D()(exp2), xx); }
// }
