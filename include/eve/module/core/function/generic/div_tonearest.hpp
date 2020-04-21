//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_DIV_TONEAREST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_DIV_TONEAREST_HPP_INCLUDED

#include <eve/concept/compatible.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/logical_ornot.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/roundings.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/shr.hpp>

#include <type_traits>

namespace eve::detail
{

  template<real_value T>
  EVE_FORCEINLINE T div_(EVE_SUPPORTS(cpu_)
                           , to_nearest_type const &
                           , T const &a
                           , T const &b) noexcept
  requires native<T>
  {
    using elt_t = element_type_t<T>;
    if   constexpr(floating_real_value<T>)
    {
      return nearest(div(a, b));
    }
    else if constexpr(integral_real_value<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if constexpr(signed_value<T>)
        {
          if constexpr(std::is_same_v<elt_t, std::int64_t>)
          {
            using ui_t = as_integer_t<T, unsigned>;
            if (!a) return  Zero<T>();
            if(b)
            {
              ui_t aa = saturated_(eve::abs)(a);
              ui_t ab = saturated_(eve::abs)(b);
              T q = to_nearest_(div)(aa, ab);
              return  if_else(is_gez(a^b), q, -q);
            }
            else return ((a>0) ? Valmax<T>() : Valmin<T>());
          }
          else
          {
            using f_t = as_floating_point_t<elt_t>;
            if (b) return saturated_(convert)(nearest(static_cast<f_t>(a)/static_cast<f_t>(b)), as<T>());
            else   return (a) ? ((a>0) ? Valmax<T>() : Valmin<T>()) : Zero<T>();
          }
        }
        else if constexpr(unsigned_value<T>)
        {
          if(b)
          {
            T q = div(a, b);
            T rx2 = 2*(a-q*b);
            if (rx2 >= b)
            {
              if ((rx2 == b) && is_even(q)) --q;
              ++q;
            }
            return q;
          }
          else return bit_mask(a);
        }
      }
      else if constexpr(simd_value<T>)
      {
        if constexpr(signed_integral_value<T>)
        {
          if constexpr(std::is_same_v<elt_t, std::int64_t>)
          {
            auto aa = saturated_(eve::abs)(a);
            auto bb = saturated_(eve::abs)(b);
            bb = if_else(is_eqz(bb), eve::allbits_, bb);
            auto q = eve::saturated_(eve::div)(aa, bb);
            auto rx2 = 2*(aa-q*bb);
            q = if_else (is_greater_equal(rx2, bb)
                        , inc[logical_ornot(rx2 != bb, is_even(q))](q)
                        , q);
            return if_else(is_nez(b)
                          , if_else(is_gez(a^b), q, -q)
                          , if_else(is_eqz(a)
                                   , eve::zero_
                                   , if_else(is_gtz(a)
                                            , Valmax<T>()
                                            , Valmin<T>()
                                            )
                                   )
                          );
          }
          else
          {
            return if_else(is_nez(b)
                          , saturated_(convert)(nearest(convert(a, double_)/
                                                        convert(b, double_)), as<elt_t>())
                          , if_else(is_eqz(a)
                                   , eve::zero_
                                   , if_else(is_gtz(a)
                                            , Valmax<T>()
                                            , Valmin<T>()
                                            )
                                   )
                          );
          }
        }
        else if constexpr(unsigned_value<T>)
        {
          auto bb = if_else(is_eqz(b), eve::allbits_, b);
          T q = div(a, bb);
          T rx2 = 2*(a-q*bb);
          q = if_else(is_greater_equal(rx2, bb)
                     ,inc[logical_ornot(rx2 != bb, is_even(q))](q)
                     , q);
          return if_else(is_nez(b), q, bit_mask(a));
        }
      }
    }
  }
}

#endif
