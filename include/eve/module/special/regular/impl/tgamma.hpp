//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/stirling.hpp>

namespace eve::detail
{
template<floating_ordered_value T, decorator D>
EVE_FORCEINLINE T
tgamma_(EVE_SUPPORTS(cpu_), D const&, T a0) noexcept
    requires(is_one_of<D>(types<regular_type, pedantic_type> {}))
{
  if constexpr( has_native_abi_v<T> )
  {
    using elt_t  = element_type_t<T>;
    auto tgamma1 = [](T x)
    {
      if constexpr( std::is_same_v<elt_t, float> )
      {
        return horn<T,
                    0X3F800000U, //  9.999999757445841E-01
                    0X3ED87799U, //  4.227874605370421E-01
                    0X3ED2D411U, //  4.117741948434743E-01
                    0X3DA82A34U, //  8.211174403261340E-02
                    0X3D93AE7CU, //  7.211014349068177E-02
                    0X3B91DB14U, //  4.451165155708328E-03
                    0X3BA90C99U, //  5.158972571345137E-03
                    0X3AD28B22U  //  1.606319369134976E-03
                    >(x);
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        return horn<T,
                    0X3FF0000000000000ULL, // 9.99999999999999996796E-1
                    0X3FDFA1373993E312ULL, // 4.94214826801497100753E-1
                    0X3FCA8DA9DCAE7D31ULL, // 2.07448227648435975150E-1
                    0X3FA863D918C423D3ULL, // 4.76367800457137231464E-2
                    0X3F8557CDE9DB14B0ULL, // 1.04213797561761569935E-2
                    0X3F5384E3E686BFABULL, // 1.19135147006586384913E-3
                    0X3F24FCB839982153ULL  // 1.60119522476751861407E-4
                    >(x)
               / horn<T,
                      0X3FF0000000000000ULL, //  1.00000000000000000320E00
                      0X3FB24944C9CD3C51ULL, //  7.14304917030273074085E-2
                      0XBFCE071A9D4287C2ULL, // -2.34591795718243348568E-1
                      0X3FA25779E33FDE67ULL, //  3.58236398605498653373E-2
                      0X3F8831ED5B1BB117ULL, //  1.18139785222060435552E-2
                      0XBF7240E4E750B44AULL, // -4.45641913851797240494E-3
                      0X3F41AE8A29152573ULL, //  5.39605580493303397842E-4
                      0XBEF8487A8400D3AFULL  // -2.31581873324120129819E-5
                      >(x);
      }
    };
    if constexpr( scalar_value<T> )
    {
      auto inftest = [](T a0)
      {
        if constexpr( std::is_same_v<elt_t, float> ) { return a0 > 35.4f; }
        else if constexpr( std::is_same_v<elt_t, double> ) { return a0 > 171.624; };
      };
      if( is_eqz(a0) ) return copysign(inf(eve::as(a0)), a0);
      if constexpr( eve::platform::supports_nans )
      {
        if( is_nan(a0) || (a0 == minf(eve::as(a0))) ) return nan(eve::as(a0));
        if( a0 == inf(eve::as(a0)) ) return a0;
      }
      auto x = a0;
      if( inftest(a0) ) return inf(eve::as(a0));
      auto q = abs(x);
      if( x < T(-33) )
      {
        T    st     = stirling(q);
        T    p      = floor(q);
        auto iseven = is_even((int32_t)p);
        if( p == q ) return nan(eve::as(a0));
        T z = q - p;
        if( z > half(eve::as(a0)) )
        {
          p += one(eve::as(a0));
          z = q - p;
        }
        z = q * sinpi(z);
        if( is_eqz(z) ) return nan(eve::as(a0));
        st = pi(eve::as(a0)) / (abs(z) * st);
        return iseven ? -st : st;
      }
      T z = one(eve::as(a0));
      while( x >= T(3) )
      {
        x -= one(eve::as(a0));
        z *= x;
      }
      while( is_ltz(x) )
      {
        z /= x;
        x += one(eve::as(a0));
      }
      while( x < T(2) )
      {
        if( is_eqz(x) ) return nan(eve::as(a0));
        z /= x;
        x += one(eve::as(a0));
      }
      if( x == T(2) ) return (z);
      x -= T(2);
      return z * tgamma1(x);
    }
    else if constexpr( simd_value<T> )
    {
      auto large_negative = [](T q)
      {
        auto st     = stirling(q);
        auto p      = floor(q);
        auto sgngam = if_else(is_even(p), one(eve::as(q)), eve::mone);
        auto z      = q - p;
        auto test2  = is_less(z, half(eve::as(q)));
        z           = dec[test2](z);
        z           = q * sinpi(z);
        z           = abs(z);
        return sgngam * pi(eve::as(q)) / (z * st);
      };
      auto other = [tgamma1](T q, const auto& test)
      {
        auto x = if_else(test, T(2), q);
        if constexpr( eve::platform::supports_nans )
        {
          auto inf_result = q == inf(eve::as<T>());
          x               = if_else(inf_result, T(2), x);
        }
        auto z     = one(eve::as<T>());
        auto test1 = (x >= T(3));
        while( eve::any(test1) )
        {
          x     = dec[test1](x);
          z     = if_else(test1, z * x, z);
          test1 = (x >= T(3));
        }
        // all x are less than 3
        test1 = is_ltz(x);
        while( eve::any(test1) )
        {
          z     = if_else(test1, z / x, z);
          x     = inc[test1](x);
          test1 = is_ltz(x);
        }
        // all x are greater than 0 and less than 3
        auto test2 = is_less(x, T(2));
        while( eve::any(test2) )
        {
          z     = if_else(test2, z / x, z);
          x     = inc[test2](x);
          test2 = is_less(x, T(2));
        }
        // all x are greater equal 2 and less than 3
        x = z * tgamma1(x - T(2));
        if constexpr( eve::platform::supports_infinites )
        {
          auto inf_result = (q == inf(eve::as<T>()));
          return if_else(inf_result, q, x);
        }
        else return x;
      };

      auto nan_result = is_ltz(a0) && is_flint(a0);
      //       if constexpr(eve::platform::supports_nans) nan_result = is_nan(a0) || nan_result;
      auto        q    = abs(a0);
      auto        test = is_less(a0, T(-33.0));
      std::size_t nb   = eve::count_true(test);
      auto        r    = nan(eve::as(a0));
      if( nb > 0 )
      {
        // treat negative large with reflection
        r = large_negative(q);
        if( nb >= cardinal_v<T> ) return if_else(nan_result, eve::allbits, r);
      }
      auto r1 = other(a0, test);
      auto r2 = if_else(test, r, r1);
      return if_else(
          is_eqz(a0), copysign(inf(eve::as(a0)), a0), if_else(nan_result, eve::allbits, r2));
    }
  }
  else return apply_over(tgamma, a0);
}

template<floating_ordered_value T>
EVE_FORCEINLINE constexpr T
tgamma_(EVE_SUPPORTS(cpu_), T const& x) noexcept
{
  return tgamma(regular_type(), x);
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
tgamma_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::tgamma, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
tgamma_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::tgamma), ts ...);
}
}
