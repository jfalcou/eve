//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_DIV_UPWARD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_DIV_UPWARD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/roundings.hpp>
#include <eve/function/shr.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>



namespace eve::detail
{

  template<real_value T>
  EVE_FORCEINLINE T div_(EVE_SUPPORTS(cpu_)
                           , upward_type const &
                           , T const &a
                           , T const &b) noexcept
  requires native<T>
  {
    using elt_t = element_type_t<T>;
    if   constexpr(floating_real_value<T>)
    {
      return ceil(div(a, b));
    }
    else if constexpr(integral_real_value<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if constexpr(signed_value<T>)
        {
          if constexpr(std::is_same_v<elt_t, std::int64_t>)
          {
            if (!a) return Zero<T>();
            if(b)
            {
              auto q = saturated_(div)(a, b);
              auto r =a-q*b;
              if (is_nez(r)&&((a^b) >= 0)) return saturated_(inc)(q);
              else                         return q;
            }
            else return ((a>0) ? Valmax<T>() : Valmin<T>());
          }
          else
          {
            if (b) return saturated_(convert)(ceil(static_cast<double>(a)/static_cast<double>(b)), as<T>());
            else   return (a) ? ((a>0) ? Valmax<T>() : Valmin<T>()) : Zero<T>();
          }
        }
        else if constexpr(unsigned_value<T>)
        {
          if(b)
          {
            T q = a/b;
            if (is_nez(a-q*b)) return inc(q);
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
            auto bb = if_else(is_eqz(b), eve::one_, b);
            auto q = saturated_(eve::div)(a, bb);
            auto r =a-q*b;
            q = saturated_(inc[is_nez(r)&&is_gez(bit_xor(a, b))])(q);
            auto z = if_else(is_gtz(a), Valmax<T>(), Valmin<T>());
            z = if_else(is_eqz(a), eve::zero_, z);
            return if_else(is_nez(b), q, z);
          }
          else
          {
            auto z = if_else(is_gtz(a), Valmax<T>(), Valmin<T>());
            z = if_else(is_eqz(a), eve::zero_, z);
            auto q =  saturated_(convert)(/*i*/ceil(convert(a, double_)/convert(b, double_)), as<elt_t>());
            return if_else(is_nez(b), q, z);
          }
        }
        else if constexpr(unsigned_value<T>)
        {
          auto bb = if_else(is_eqz(b), eve::allbits_, b);
          T q = saturated_(div)(a, bb);
          q = inc[is_nez(a-q*b)](q);
          return if_else(is_nez(b), q, bit_mask(a));
        }
      }
    }
  }
}

#endif
