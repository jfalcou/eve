//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/wide_forward.hpp>

namespace eve
{
template<logical_simd_value Logical> struct top_bits;

struct ignore_all_;
struct ignore_none_;
struct keep_first;
struct keep_last;
struct ignore_first;
struct ignore_last;
struct keep_between;
struct ignore_extrema;
}

namespace eve::detail
{
// to_logical -----------------------------------------------------------
template<typename T, typename N> auto to_logical(wide<T, N> const& v) noexcept;

template<value T> EVE_FORCEINLINE auto to_logical(logical<T> v) noexcept;

template<logical_simd_value Logical> Logical to_logical(eve::top_bits<Logical> mmask) noexcept;

template<scalar_value T> auto to_logical(T v) noexcept;

template<relative_conditional_expr C, simd_value T> auto to_logical(C c, eve::as<T>) noexcept;

template<relative_conditional_expr C, simd_value T>
auto EVE_FORCEINLINE to_logical(C c, eve::as<T>) noexcept requires(current_api >= avx512);
}
