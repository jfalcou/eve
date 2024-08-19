//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/arch/platform.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/as.hpp>

#include <array>
#include <cstddef>
#include <type_traits>

namespace eve::detail
{
  //================================================================================================
  // Full slice
  //================================================================================================
  template<typename P> EVE_FORCEINLINE auto slice_impl(P const &a) noexcept
  {
    using abi_t   = typename P::abi_type;

    if constexpr( is_aggregated_v<abi_t> )  return a.storage().slice();
    else                                    return std::array{a.slice(lower_), a.slice(upper_)};
  }

  //================================================================================================
  // Partial slice
  //================================================================================================
  template<typename P, typename Slice>
  EVE_FORCEINLINE auto slice_impl(P const &a, Slice s) noexcept
  {
    using abi_t   = typename P::abi_type;
    using card_t  = typename P::cardinal_type;
    using value_t = typename P::value_type;

    using sub_t = as_wide_t<value_t, typename card_t::split_type>;

    if constexpr( is_emulated_v<abi_t> )
    {
      auto eval = [&](auto... I) { return sub_t {a.get(I + (Slice::value * sub_t::size()))...}; };

      return apply<card_t::value / 2>(eval);
    }
    else if constexpr( is_aggregated_v<abi_t> )
    {
      return a.storage().slice()[Slice::value];
    }
    else if constexpr( is_bundle_v<abi_t> )
    {
      return sub_t(kumi::map( [&](auto m) { return m.slice(s); }, a));
    }
  }

  //================================================================================================
  // Logical slices
  //================================================================================================
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE auto slice_(EVE_REQUIRES(cpu_), O const&, logical<wide<T, N>> a) noexcept
  {
    if constexpr (is_native_v<abi_t<T, N>> && abi_t<T, N>::is_wide_logical)
    {
      using l_t   = logical<wide<T, typename N::split_type>>;
      using s_t   = typename l_t::storage_type;
      using t_t   = std::array<l_t, 2>;
      auto [l, h] = a.mask().slice();
      return t_t {l_t(bit_cast(l.storage(), as<s_t>())), l_t(bit_cast(h.storage(), as<s_t>()))};
    }
    else if constexpr (non_native_abi<abi_t<T, N>>)
    {
      return slice_impl(a);
    }
  }

  template<callable_options O, typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice_(EVE_REQUIRES(cpu_), O const&, logical<wide<T, N>> a, Slice s) noexcept
  {
    if constexpr (is_native_v<abi_t<T, N>> && abi_t<T, N>::is_wide_logical)
    {
       using l_t = logical<wide<T, typename N::split_type>>;
      using s_t = typename l_t::storage_type;
      return l_t( bit_cast(a.mask().slice(s).storage(), as<s_t>()) );
    }
    else if constexpr (non_native_abi<abi_t<T, N>>)
    {
      return slice_impl(a);
    }
  }

  //================================================================================================
  // Arithmetic slices
  //================================================================================================
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE auto slice_(EVE_REQUIRES(cpu_), O const&, wide<T, N> a) noexcept
      requires non_native_abi<abi_t<T, N>>
  {
    return slice_impl(a);
  }

  template<callable_options O, arithmetic_scalar_value T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice_(EVE_REQUIRES(cpu_), O const&, wide<T, N> a, Slice s) noexcept
      requires non_native_abi<abi_t<T, N>>
  {
    return slice_impl(a, s);
  }
}
