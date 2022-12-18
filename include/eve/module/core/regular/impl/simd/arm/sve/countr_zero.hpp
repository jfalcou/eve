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
template<unsigned_scalar_value T, typename N>
EVE_FORCEINLINE auto
countr_zero_(EVE_SUPPORTS(sve_), wide<T, N> v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  return countr_zero[ignore_none](v);
}

template<conditional_expr C, unsigned_scalar_value T, typename N>
EVE_FORCEINLINE auto
countr_zero_(EVE_SUPPORTS(sve_), C const& cond, wide<T, N> v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete && C::is_inverted )
  {
    return countl_zero(wide<T,N>(svrbit_x(detail::sve_true<T>(),v)));
  }
  else
  {
    return svclz_m( alternative(cond, v, as(v))
                  , expand_mask(cond, as(v))
                  , svrbit_x(detail::sve_true<T>(),v)
                  );
  }
}
}
