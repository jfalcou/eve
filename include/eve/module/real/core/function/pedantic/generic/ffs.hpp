//==================================================================================================
/*
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<unsigned_value T>
  EVE_FORCEINLINE constexpr T ffs_(EVE_SUPPORTS(cpu_)
                                  , pedantic_type const &
                                  , T const &a0) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr(has_native_abi_v<T>)
      return if_else(is_nez(a0), ffs(a0), T(sizeof(elt_t)*8));
    else return apply_over(pedantic(ffs), a0);
  }

}
