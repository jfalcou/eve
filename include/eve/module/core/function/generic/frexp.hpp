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
#include <eve/function/convert.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/regular.hpp>

#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // tagged cases
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_), D const &, T const &a0) noexcept
  {
    auto [m, e] = D()(ifrexp)(a0);
    return std::make_tuple(m, to_<T>(e));
  }

  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    auto [m, e] = ifrexp(a0);
    return std::make_tuple(m, to_<T>(e));
  }
}
