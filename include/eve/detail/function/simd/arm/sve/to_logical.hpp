//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<typename T, typename N>
EVE_FORCEINLINE auto
to_logical(wide<T, N> const& v) noexcept requires sve_abi<abi_t<T, N>>
{
  return v != 0;
}
}
