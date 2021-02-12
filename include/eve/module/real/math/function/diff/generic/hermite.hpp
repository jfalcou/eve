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

#include <eve/function/hermite.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<integral_value N, floating_real_value T>
  EVE_FORCEINLINE constexpr T hermite_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  requires index_compatible_values<N, T>&& has_native_abi_v<T> && has_native_abi_v<N>
  {
     using elt_t = element_type_t<T>;
     return 2*convert(n, as(elt_t()))*hermite(dec(n), x);
  }
}
