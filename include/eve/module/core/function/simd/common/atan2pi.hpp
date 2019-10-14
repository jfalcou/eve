//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ATAN2PI_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ATAN2PI_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/inpi.hpp>
#include <eve/function/atan.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/platform.hpp>
#include <eve/concept/vectorized.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto atan2pi_( EVE_SUPPORTS(cpu_)
                                        , T const &a0
                                        , U const &a1
                                        ) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating,T>,
            floating<value_type_t<U>>
          )
  {
    return inpi(atan2(a0, a1));
  }


  template<typename T, typename U>
  EVE_FORCEINLINE auto atan2pi_( EVE_SUPPORTS(cpu_)
                             , pedantic_type const &
                             , T const &a0
                             , U const &a1
                             ) noexcept
  requires( std::conditional_t<is_vectorized_v<T>,T,U>,
            detail::either<is_vectorized_v<T>, is_vectorized_v<U>>,
            behave_as<floating,T>,
            floating<value_type_t<U>>
          )
  {
    return inpi(pedantic_(atan2)(a0, a1));
  }
}

#endif
