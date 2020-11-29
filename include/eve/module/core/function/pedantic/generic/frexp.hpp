//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Jean-Thierry LAPRESTE
   Copyright 2020 Joel FALCOU

   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/pedantic/ifrexp.hpp>
#include <eve/function/pedantic.hpp>

#include <tuple>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a0) noexcept
  {
    auto [m, e] = pedantic(ifrexp)(a0);
    return std::make_tuple(m, to_<T>(e));
  }
}
