//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/simd/x86/flags.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
//================================================================================================
// Wide to Logical
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
to_logical(wide<T, N> const& v) noexcept requires x86_abi<abi_t<T, N>>
{
  return v != 0;
}

template<relative_conditional_expr C, simd_value T>
auto EVE_FORCEINLINE
to_logical(C c, eve::as<T>) noexcept requires(current_api >= avx512)
{
  using type = as_logical_t<T>;
  auto value = top_bits<type>(c);
  return detail::to_logical(value);
}
}
