//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_NOTAND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BITWISE_NOTAND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto bitwise_notand_(EVE_SUPPORTS(cpu_)
                                       , T const &a
                                       , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;    
    using vt_t = value_type_t<T>; 
    if constexpr(is_vectorizable_v<U> && !std::is_same_v<vt_t, U> && (sizeof(U) == sizeof(vt_t)))
      // this will ensure that no scalar conversion will take place in aggregated
      // in the case vector and scalar not of the value type
    {
      return eve::bitwise_notand(a, T(bitwise_cast<vt_t>(b)));
    }
    else if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::bitwise_notand, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::bitwise_notand, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_vectorized_v<T> && !is_vectorized_v<U> )
    {
      return eve::bitwise_notand(a, T{b} );
    }
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      return eve::bitwise_notand(a, bitwise_cast<T>(b) );
    }
    else
    {
      static_assert( wrong<T,U>, "[eve::bitwise_notand] - Unsupported types pairing");
      return {}; 
    }
  }
}

#endif
