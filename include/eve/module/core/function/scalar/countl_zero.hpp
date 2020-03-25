//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COUNTL_ZERO_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COUNTL_ZERO_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ffs.hpp>
#include <eve/function/bit_reverse.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/zero.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto countl_zero_(EVE_SUPPORTS(cpu_), T const &a0)  noexcept
  Requires(as_integer_t<T, unsigned>, Vectorizable<T>
  {
    using i_t = as_integer_t<v_t, unsigned>; 
    if (is_eqz(a0)) return Zero<i_t>(); 
    if constexpr(std::is_signed_v<v_t>)
    {
      return countl_zero(bit_cast(a0, as<i_t>()));
    }
    else if constexpr(std::is_same<T, std::uint64_t>)
    {
      #ifdef __GNUC__
      return __builtin_clzll(t1);
      #else
      return ffs(bit_reverse(t1))-1;
      #endif
    }
    else if constexpr(std::is_same<T, std::uint32_t>)
    {
      #ifdef __GNUC__
      return __builtin_clz(t1);
      #else
      return ffs(bit_reverse(t1))-1;
      #endif
    }
    else 
    {
      return countl_zero(static_cast<uint32_t>(t1))-sizeof(T)*8;
    }       
  }
}

#ea0dif
