//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_select.hpp>
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
  if_else_( EVE_SUPPORTS(cpu_), T const &cond, U const &t, U const &f
          , satisfy(Vectorized<T>, Vectorized<U>, EqualCardinal<T,U> )
          ) noexcept
  {
    auto cond_mask = bitwise_mask(cond);
    return bitwise_select( cond_mask, t, f);
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_( EVE_SUPPORTS(cpu_), T const &cond, logical<U> const &t, logical<U> const &f
          , satisfy(Vectorized<T>, Vectorized<logical<U>>, EqualCardinal<T,logical<U>> )
          ) noexcept
  {
    auto cond_mask = bitwise_mask(cond);
    return bitwise_cast<logical<U>>(bitwise_select(cond_mask, t.mask(), f.mask()));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_( EVE_SUPPORTS(cpu_) , T const &cond, U const &t, U const &f
          , satisfy(Vectorized<T>, Vectorizable<U>)
          ) noexcept
  {
    using v_t = as_wide_t<U,typename T::cardinal_type>;
    return if_else(cond,v_t(t),v_t(f));
  }

  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto
  if_else_( EVE_SUPPORTS(cpu_) , T const &cond, U const &t, V const &f
          , satisfy(Vectorized<T>, detail::If< is_vectorized_v<U> != is_vectorized_v<V>>)
          ) noexcept
  {
    if constexpr(is_vectorized_v<U>)
    {
      return eve::if_else(cond, t, U(f));
    }
    else
    {
      return eve::if_else(cond, V(t), f);
    }
  }
}

#endif

#include "if_else_zero.hpp"
#include "if_zero_else.hpp"
#include "if_else_allbits.hpp"
#include "if_allbits_else.hpp"
#include "if_else_one.hpp"
