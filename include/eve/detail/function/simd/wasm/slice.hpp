//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  //================================================================================================
  // Single slice
  //================================================================================================
  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE wide<T, typename N::split_type>
  slice(wide<T,N> const &a, Slice const &) noexcept
      requires wasm_abi<abi_t<T, N>>
  {
    using sub_t = as_wide_t<T, typename N::split_type>;

    auto eval = [&](auto... I) { return sub_t {a.get(I + (Slice::value * sub_t::size()))...}; };
    return apply<N::value / 2>(eval);
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
  slice(logical<wide<T,N>> const &a, Slice const &) noexcept
      requires wasm_abi<abi_t<T, N>>
  {
    using l_t = logical<wide<T, typename N::split_type>>;
    using s_t = typename l_t::storage_type;
    return l_t( bit_cast(a.mask().slice(Slice{}).storage(), as<s_t>()) );
  }

  //================================================================================================
  // Both slice
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N> const &a) noexcept
      requires wasm_abi<abi_t<T, N>>
  {
    std::array<wide<T, typename N::split_type>, 2> that{slice(a, lower_), slice(a, upper_)};
    return that;
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(logical<wide<T,N>> const &a) noexcept
      requires wasm_abi<abi_t<T, N>>
  {
    std::array<logical<wide<T, typename N::split_type>>,2> that{slice(a, lower_), slice(a, upper_)};
    return that;
  }
}
