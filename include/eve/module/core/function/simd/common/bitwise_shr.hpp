//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/shr.hpp>
#include <eve/forward.hpp>
#include <type_traits>


// -------------------------------------------------------------------------------------------------
// Basic
namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto bitwise_shr_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires( T, Vectorized<T>, Integral<value_type_t<U>>, Integral<value_type_t<T>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;
    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return  map( eve::bitwise_shr, a, b );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::bitwise_shr, a, b );
    }
    else
    {
      if constexpr( is_vectorizable_v<U>)
      {
        using su_t = as_integer_t<value_type_t<T>, unsigned>;
        using u_t = wide < su_t, typename T::cardinal_type, t_abi>; 
        return bitwise_cast<T>(eve::shr(bitwise_cast<u_t>(a), int(b))); 
      }
      else
      {
       return bitwise_cast<T>(map( eve::bitwise_shr, a, b)); 
      }
    }   
  }
}


#endif
