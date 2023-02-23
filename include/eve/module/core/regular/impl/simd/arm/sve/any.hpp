//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/remove_garbage.hpp>

namespace eve::detail
{
template<scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(sve_), C const& cond, logical<wide<T,N>> v) noexcept
requires sve_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete )
  {
    if constexpr( C::is_inverted )
    {
      using ec_t  = expected_cardinal_t<T, typename logical<wide<T,N>>::abi_type>;
      return svptest_any(keep_first(N::value).mask(as<wide<T,ec_t>>{}), v);
    }
    else                            return false;
  }
  else return svptest_any(cond.mask(as<wide<T,N>>{}),v);
}
}
