//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/module/core.hpp>


namespace eve::detail
{
  template<floating_ordered_value T, typename Engine>
  EVE_FORCEINLINE auto urg01(Engine& eng, as<T> const &) noexcept
  requires (scalar_value<T>)
  {
    if constexpr(scalar_value<T>)
    {
      for(;;) {
        T numerator = static_cast<T>(eng() - (eng.min)());
        T divisor = static_cast<T>((eng.max)() - (eng.min)());
        EVE_ASSERT(eve::all(divisor > T(0)), "divisor is negative");
        EVE_ASSERT(eve::all(numerator >= T(0) && numerator <= divisor), "numerator negative or greater than divisor");
        T result = numerator / divisor;
        if(result < one(as(result))) return result;
      }
    }
    else
    {
      using elt_t = element_type_t<T>;
      return [&]<std::size_t... I>( std::index_sequence<I...>)
      {
        auto v = [&](auto) { return detail::urg01(eng, as<elt_t>()); };
        return T{ v(I)...};
      }( std::make_index_sequence< cardinal_v<T>>{});
    }
  }
}
