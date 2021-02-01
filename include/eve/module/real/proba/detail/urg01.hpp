//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2021 Joel FALCOU
  Copyright 2021 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/one.hpp>

namespace eve::detail
{
  template<floating_real_scalar_value T, typename Engine>
  EVE_FORCEINLINE auto urg01(Engine& eng, as_<T> const &) noexcept
  {
    for(;;) {
      T numerator = static_cast<T>(eng() - (eng.min)());
      T divisor = static_cast<T>((eng.max)() - (eng.min)());
//       EVE_ASSERT(all(divisor > T(0)), "divisor is negative");
//       EVE_ASSERT(all(numerator >= T(0) && numerator <= divisor), "numerator negative or greater than divisor");
      T result = numerator / divisor;
      if(result < one(as(result))) return result;
    }
  }

  template<floating_real_simd_value T, typename Engine>
  EVE_FORCEINLINE auto urg01(Engine& eng, as_<T> const &) noexcept
  {
    using elt_t = element_type_t<T>;
    return [&]<std::size_t... I>( std::index_sequence<I...>)
      {
        auto v = [&](auto) { return detail::urg01(eng, as<elt_t>()); };
        return T{ v(I)...};
      }( std::make_index_sequence< cardinal_v<T>>{});
  }
}
