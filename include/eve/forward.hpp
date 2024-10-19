//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/traits/as_logical.hpp>

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
  template<typename T, typename N> logical<wide<T, N>> to_logical(wide<T, N> const& v) noexcept;

  template<value T> EVE_FORCEINLINE logical<T> to_logical(logical<T> v) noexcept;

  template<logical_simd_value Logical> Logical to_logical(eve::top_bits<Logical> mmask) noexcept;

  template<scalar_value T> logical<T> to_logical(T v) noexcept;

  template<relative_conditional_expr C, simd_value T> as_logical_t<T> to_logical(C c, as<T>) noexcept;

  template<relative_conditional_expr C, simd_value T>
  auto EVE_FORCEINLINE to_logical(C c, as<T>) noexcept requires(current_api >= avx512);

  template<conditional_expr C, typename Op, typename Arg0, typename... Args>
  EVE_FORCEINLINE auto mask_op(C const&                     c,
                              [[maybe_unused]] Op          f,
                              [[maybe_unused]] Arg0 const& a0,
                              [[maybe_unused]] Args const&...as);


  // This is an inderect wrapper of eve::simd_cast to avoid cycling dependencies
  template <typename From, typename To>
  To call_simd_cast(From, as<To>);
}
