//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/constant/maxlog2.hpp>
#include <eve/module/math/constant/minlog2.hpp>
#include <eve/module/math/constant/minlog2denormal.hpp>

namespace eve::detail
{
template<floating_real_value T, decorator D>
EVE_FORCEINLINE constexpr T
exp2_(EVE_SUPPORTS(cpu_), D const&, T x) noexcept
    requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    using elt_t    = element_type_t<T>;
    auto minlogval = []()
    {
      if constexpr( !eve::platform::supports_denormals || std::is_same_v<D, regular_type> )
        return minlog2(eve::as<T>());
      else return minlog2denormal(eve::as<T>());
    };
    auto xltminlog2 = x <= minlogval();
    auto xgemaxlog2 = x >= maxlog2(eve::as(x));
    if constexpr( scalar_value<T> )
    {
      if( xgemaxlog2 ) return inf(eve::as(x));
      if( xltminlog2 ) return zero(eve::as(x));
    }
    auto k = nearest(x);
    x      = x - k;
    if constexpr( std::is_same_v<elt_t, float> )
    {
      T y = horn<T, 0x3e75fdf1, 0x3d6356eb, 0x3c1d9422, 0x3ab01218, 0x3922c8c4>(x);
      x   = inc(fma(y, sqr(x), x * log_2(eve::as<T>())));
    }
    else if constexpr( std::is_same_v<elt_t, double> )
    {
      x *= log_2(eve::as<T>());
      T    t = sqr(x);
      auto h = horn<T,
                    0x3fc555555555553eull,
                    0xbf66c16c16bebd93ull,
                    0x3f11566aaf25de2cull,
                    0xbebbbd41c5d26bf1ull,
                    0x3e66376972bea4d0ull>(t);
      T    c = fnma(t, h, x); // x-h*t
      x      = oneminus(((-(x * c) / (T(2) - c)) - x));
    }
    auto z = pedantic(ldexp)(x, k);
    if constexpr( simd_value<T> )
    {
      z = if_else(xltminlog2, eve::zero, z);
      z = if_else(xgemaxlog2, inf(eve::as(x)), z);
    }
    return z;
  }
  else { return apply_over(D()(exp2), x); }
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr T
exp2_(EVE_SUPPORTS(cpu_), T const& x) noexcept
{
  return exp2(regular_type(), x);
}

////////////////////////////////////////////////////////////////////////////////////
// integral types

template<integral_real_value T, typename D>
EVE_FORCEINLINE constexpr auto
exp2_(EVE_SUPPORTS(cpu_), D const&, T xx) noexcept
    requires(is_one_of<D>(types<converter_type<float>,
                                converter_type<double>,
                                floating_converter,
                                pedantic_type,
                                raw_type,
                                regular_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( is_one_of<D>(
                      types<converter_type<float>, converter_type<double>, floating_converter> {}) )
    {
      using b_t  = std::conditional_t<std::is_same_v<D, floating_converter>,
                                     eve::as_floating_point_t<T>,
                                     typename D::base_type>;
      using vd_t = typename b_t::value_type;
      using i_t  = as_integer_t<vd_t>;

      auto x  = to_<i_t>(xx);
      auto z  = is_nez(x);
      auto zz = eve::min(x + maxexponent(eve::as<vd_t>()), 2 * maxexponent(eve::as<vd_t>()) + 1)
                & z.mask();
      zz        = zz << nbmantissabits(eve::as<vd_t>());
      using r_t = std::conditional_t<scalar_value<T>, vd_t, wide<vd_t, cardinal_t<T>>>;
      return if_else(z, bit_cast(zz, as<r_t>()), one);
    }
    else
    {
      element_type_t<T> constexpr siz = sizeof(element_type_t<T>) * 8 - 1;
      auto test                       = is_ltz(xx) || (xx > siz);
      xx                              = if_else(test, zero, xx);
      auto tmp                        = if_else(test, eve::zero, shl(one(eve::as(xx)), xx));
      if constexpr( std::is_same_v<D, saturated_type> )
      {
        using elt_t = element_type_t<T>;
        return if_else(is_gez(xx, T(sizeof(elt_t))), valmax(eve::as<T>()), tmp);
      }
      else return tmp;
    }
  }
  else { return apply_over(D()(exp2), xx); }
}

template<integral_real_value T>
EVE_FORCEINLINE constexpr auto
exp2_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  return exp2(regular_type(), x);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
exp2_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::exp2, t);
}
}
