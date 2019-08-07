//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_AVERAGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_AVERAGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/abi_cast.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE  auto average_(EVE_SUPPORTS(cpu_)
                                , T const &a
                                , U const &b) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
          )
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr( is_emulated_v<t_abi> || is_emulated_v<u_abi> )
    {
      return map( eve::average, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_aggregated_v<t_abi> || is_aggregated_v<u_abi> )
    {
      return aggregate( eve::average, abi_cast<value_type_t<U>>(a), abi_cast<value_type_t<T>>(b) );
    }
    else if constexpr( is_vectorized_v<T> || is_vectorized_v<U> )
    {
      return eve::average(abi_cast<U>(a), abi_cast<T>(b) );
    }
    else
    {
      static_assert( std::is_same_v<T,U>, "[eve::average] - Incompatible types.");
      return {};
    }
  }
}

#endif
