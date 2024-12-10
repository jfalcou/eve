//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename U, typename N>
  EVE_FORCEINLINE logical<wide<T, N>> logical_or_(EVE_REQUIRES(sve_), O const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
    requires(sve_abi<abi_t<T, N>> || sve_abi<abi_t<U, N>>)
  {
    return svorr_z(sve_true<T>(), v, convert(w, as<logical<T>>{}));
  }
}
