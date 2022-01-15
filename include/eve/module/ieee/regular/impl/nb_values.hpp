//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/ieee/detail/next_kernel.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto nb_values_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires std::same_as<element_type_t<U>, element_type_t<T>>
  {

    return arithmetic_call(nb_values, a, b);
  }

  template<value T>
  EVE_FORCEINLINE auto nb_values_(EVE_SUPPORTS(cpu_)
                                 , T const &a
                                 , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    using ui_t = as_integer_t<T, unsigned>;
    if constexpr(floating_value<T>)
    {
      auto aa = eve::detail::bitinteger(a);
      auto bb = eve::detail::bitinteger(b);
      auto z = if_else (is_unordered(a, b)
                       , eve::valmax(eve::as<ui_t>())
                       , bit_cast(dist(bb, aa), as<ui_t>())
                       );
      return inc[is_ltz(signnz(a)*signnz(b))](z);
    }
    else if constexpr(integral_value<T>)
    {
      return bit_cast(dist(a, b), as<ui_t>());
    }
  }
}
