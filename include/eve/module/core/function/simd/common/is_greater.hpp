//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_GREATER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IS_GREATER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_not.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto is_greater_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
                            requires( as_logical_t<std::conditional_t<is_vectorized_v<T>,T,U>>,
                                      detail::Either<is_vectorized_v<T>, is_vectorized_v<U>>
                                    )
  {
    // If one of argument is not Vectorized, recall once vectorized
    if constexpr( is_vectorized_v<T> && !is_vectorized_v<U> )
    {
      return is_greater(a, T{b});
    }
    else if constexpr( !is_vectorized_v<T> && is_vectorized_v<U> )
    {
      return is_greater(U{a},b);
    }
    // Both arguments are vectorized ...
    else if constexpr( is_vectorized_v<T> && is_vectorized_v<U> )
    {
      if constexpr( is_aggregated_v<typename T::abi_type> )
      {
        // ... and are aggregates
        return aggregate( eve::is_greater, a, b);
      }
      else if constexpr( is_emulated_v<typename T::abi_type> )
      {
        // ... and are emulations
        return map( eve::is_greater, a, b);
      }
      else
      {
        static_assert( wrong<T,U>, "[eve::is_greater] - Unsupported ABI.");
        return {};
      }
    }
    else
    {
      static_assert( std::is_same_v<T,U>, "[eve::is_greater] - Incompatible types.");
      return {};
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto is_greater_( EVE_SUPPORTS(cpu_),
                                            logical<T> const &a, logical<U> const &b
                                          ) noexcept
                            requires( as_logical_t<std::conditional_t<is_vectorized_v<T>,T,U>>,
                                      Vectorized<T>, Vectorized<U>
                                    )
  {
    using r_t = as_logical_t<std::conditional_t<is_vectorized_v<T>,T,U>>;
    return bitwise_cast<r_t>( is_greater(a.bits(),b.bits()) );
  }
}

#endif
