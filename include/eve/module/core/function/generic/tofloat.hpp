//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/convert.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto tofloat_(EVE_SUPPORTS(cpu_)
                                         , T const &a) noexcept
  {
    using vt_t = element_type_t<T>;
    if constexpr( floating_value<T> )      return a;
    else if constexpr(sizeof(vt_t) <= 4)   return convert(a, single_);
    else if constexpr(sizeof(vt_t) == 8)   return convert(a, double_);
  }

  template<real_value T, typename Tag>
  EVE_FORCEINLINE constexpr auto tofloat_(EVE_SUPPORTS(cpu_)
                                         , Tag const&
                                         , T const &a) noexcept
  {
    using vt_t = element_type_t<T>;
    if constexpr( floating_value<T> ) return a;
    else if constexpr(sizeof(vt_t) <= 4)   return Tag()(convert)(a, single_);
    else if constexpr(sizeof(vt_t) == 8)   return Tag()(convert)(a, double_);
  }
}

