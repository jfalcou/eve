//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_MONE_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_MONE_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/constant/one.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/ext/as_wide.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_( EVE_SUPPORTS(cpu_)
          , T const &cond
          ,  eve::callable_mone_ const &
          , U const &t
          , satisfy(Vectorized<T>, Vectorized<U>, EqualCardinal<T,U> )
          ) noexcept
  {
    if constexpr(std::is_integral_v<U>)
      return  bitwise_or(t,bitwise_mask(cond));
    else
      return  if_else(cond,eve::Mone<U>(),t);
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_( EVE_SUPPORTS(cpu_)
          , T const &cond
          ,  eve::callable_mone_ const &
          , U const &t
          , satisfy(Vectorized<T>, Vectorizable<U>)
          ) noexcept
  {
    using v_t = as_wide_t<U,typename T::cardinal_type>;
    return if_else(cond,eve::mone_,v_t(t));
  }
}

#endif
