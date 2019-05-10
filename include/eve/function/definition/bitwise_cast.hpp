//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_DEFINITION_BITWISE_CAST_HPP_INCLUDED
#define EVE_FUNCTION_DEFINITION_BITWISE_CAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_DECLARE_CALLABLE(bitwise_cast_)

  template<typename Target, typename Origin>
  auto bitwise_cast(Origin const &o) noexcept
      -> decltype(detail::callable_object<tag::bitwise_cast_>{}(o, as_<Target>{}))
  {
    return detail::callable_object<tag::bitwise_cast_>{}(o, as_<Target>{});
  }
}

#endif
