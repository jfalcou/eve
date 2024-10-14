//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> bit_reverse_(EVE_REQUIRES(sve_),
                                          O          const&,
                                          wide<T, N> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return svrbit_x(sve_true<T>(),v));
  }

  template<conditional_expr C, unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> bit_reverse_(EVE_REQUIRES(sve_),
                                          C          const& mask,
                                          wide<T, N> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, v, as(v));
    if constexpr( C::is_complete)
      return alt;
    else
    {
      auto m = expand_mask(mask, as(v));
      return svrbit_m(m, v);
    }
  }
}
