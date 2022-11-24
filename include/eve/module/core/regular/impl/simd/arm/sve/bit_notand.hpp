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
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<scalar_value T, typename N>
EVE_FORCEINLINE auto
bit_notand_(EVE_SUPPORTS(sve_), wide<T, N> const& v0, wide<T, N> const& v1) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  using i_t = typename wide<T, N>::template rebind<as_integer_t<T>,N>;
  constexpr auto tgt = as<i_t>();
  return bit_cast ( i_t ( svbic_x ( sve_true<T>()
                                  , bit_cast(v1,tgt)
                                  , bit_cast(v0,tgt)
                                  )
                        )
                  , as<wide<T,N>>{}
                  );
}
}
