//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_TOUINT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_TOUINT_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/convert.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto touint_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    using i_t = as_integer_t<value_type_t<T>, unsigned>;
    if constexpr( unsigned_value<T> ) return a;
    else                              return convert(a, as_<i_t>());
  }

  template<real_value T, typename Tag>
  EVE_FORCEINLINE constexpr auto touint_(EVE_SUPPORTS(cpu_)
                                       , Tag const&
                                       , T const &a) noexcept
  {
    using i_t = as_integer_t<value_type_t<T>, unsigned>;
    if constexpr( unsigned_value<T> ) return a;
    else                              return Tag()(convert)(a, as_<i_t>());
  }
}

#endif
