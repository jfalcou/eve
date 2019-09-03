//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

//-------------------------------------------------------------------------------------------------
// Basic
namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto
  shr_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept requires(T,
                                                                     Vectorized<T>,
                                                                     Integral<value_type_t<U>>,
                                                                     Integral<value_type_t<T>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>) { return map(eve::shr, a, b); }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::shr, a, b);
    }
    else
    {
      return map(eve::shr, a, b);
    }
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator>>(T const &v0, U const &v1) noexcept -> decltype(eve::shr(v0, v1))
  {
    return eve::shr(v0, v1);
  }
}

#endif
