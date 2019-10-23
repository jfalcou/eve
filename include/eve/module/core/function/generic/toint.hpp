//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_TOINT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_TOINT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/convert.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr as_integer_t<T>
  toint_(EVE_SUPPORTS(cpu_)
        , T const &a) noexcept
  {
    if constexpr( std::is_integral_v< value_type_t<T> > )
    {
      return a;
    }
    else
    {
      return convert(a, as_<as_integer_t<value_type_t<T>>>());
    }
  }

  template<typename T, typename Tag>
  EVE_FORCEINLINE constexpr as_integer_t<T>
  toint_(EVE_SUPPORTS(cpu_)
        , Tag const& tag_
        , T const &a) noexcept
  {
    if constexpr( std::is_integral_v< value_type_t<T> > )
    {
      return a;
    }
    else
    {
      return tag_(convert)(a, as_<as_integer_t<value_type_t<T>>>());
    }
  }
}

#endif
