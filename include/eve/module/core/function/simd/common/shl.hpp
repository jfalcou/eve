//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SHL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_SHL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto shl_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires( T, Vectorized<T>, Integral<value_type_t<U>>, Integral<value_type_t<T>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return  map(eve::shl, a, b);
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate(eve::shl, a, b );
    }
    else
    {
      return map(eve::shl, a, b);
    }   
  }
}

namespace eve
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto operator <<(T const &v0
                                  , U const &v1) noexcept
  -> decltype( eve::shl(v0,v1) )
  {
    return eve::shl(v0, v1);
  }
}
  
#endif
