//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/saturate.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto mul_(EVE_SUPPORTS(cpu_)
                            ,  saturated_type const &
                            , T const &a
                            , U const &b) noexcept
  Requires( std::conditional_t<is_Vectorized_v<T>,T,U>,
            detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::saturated_(eve::mul), abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      auto that = aggregate ( eve::saturated_(eve::mul)
                            , abi_cast<value_type_t<U>>(a)
                            , abi_cast<value_type_t<T>>(b)
                            );
      return that;
    }
    else if constexpr( is_Vectorized_v<T> && is_Vectorized_v<U> )
    {
      if constexpr(std::is_same_v<T, U>)
      {
        using vt_t = value_type_t<T>;
        if constexpr(std::is_floating_point_v<vt_t>)
        {
          return mul(a, b);
        }
        else if constexpr(sizeof(vt_t) <= 4)
        {
          using sup_t =  upgrade_t<vt_t>;
          auto z =  mul(convert(a, as<sup_t>()), convert(b, as<sup_t>()));
          auto s =  saturate(z, as<vt_t>()); //TODO saturated_(convert) ?
          return convert(s, as<vt_t>());
        }
        else
        {
          auto that = map( eve::saturated_(eve::mul), a, b);
          return that;
        }
      }
      else
      {
        static_assert(wrong<T, U>, "[eve::mul] - Missing implementationi");
        return {};
      }
    }
    else //if constexpr( is_Vectorized_v<T> || is_Vectorized_v<U> )
    {
      return eve::saturated_(eve::mul)(abi_cast<U>(a), abi_cast<T>(b) );
    }
  }
}

#endif

#include "if_mul.hpp"
