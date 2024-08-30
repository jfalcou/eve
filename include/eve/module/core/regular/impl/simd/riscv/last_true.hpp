//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/convert.hpp>

namespace eve::detail
{

template<arithmetic_scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
last_true_(EVE_SUPPORTS(rvv_), C const& cond, top_bits<logical<wide<T, N>>> const& v0) noexcept
requires rvv_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete && !C::is_inverted ) return std::nullopt;
  else
  {
    auto                m      = cond.mask(as<wide<T, N>> {});
    logical<wide<T, N>> masked = __riscv_vmand(v0.storage, m, N::value);
    return last_true(masked);
  }
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                last_true_(EVE_SUPPORTS(rvv_), top_bits<logical<wide<T, N>>> const                &v0) noexcept
requires rvv_abi<abi_t<T, N>>
{
  // TODO: optimize.
  for( int i = N::value - 1; i > -1; --i )
  {
    if( v0.get(i) ) return i;
  }
  return {};
}
}
