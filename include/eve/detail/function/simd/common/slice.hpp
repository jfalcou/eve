//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/platform.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/as.hpp>

#include <cstddef>
#include <type_traits>

namespace eve
{
  struct upper_slice : std::integral_constant<std::size_t, 1>
  {
  };
  struct lower_slice : std::integral_constant<std::size_t, 0>
  {
  };

  inline constexpr upper_slice const upper_ = {};
  inline constexpr lower_slice const lower_ = {};
}

namespace eve::detail
{
  //================================================================================================
  // Full slice
  //================================================================================================
  template<typename P> EVE_FORCEINLINE auto slice_impl(P const &a) noexcept
  {
    using abi_t   = typename P::abi_type;
    using card_t  = typename P::cardinal_type;
    using value_t = typename P::value_type;

    using sub_t = as_wide_t<value_t, typename card_t::split_type>;

    if constexpr( is_emulated_v<abi_t> )
    {
      auto eval = [&](auto... I) {
        using that_t = std::array<sub_t, 2>;
        return that_t {sub_t {a.get(I)...}, sub_t {a.get(I + card_t::value / 2)...}};
      };

      return apply<card_t::value / 2>(eval);
    }
    else if constexpr( is_aggregated_v<abi_t> )
    {
      return a.storage().segments;
    }
  }

  //================================================================================================
  // Partial slice
  //================================================================================================
  template<typename P, typename Slice>
  EVE_FORCEINLINE auto slice_impl(P const &a, Slice const &) noexcept
  {
    using abi_t   = typename P::abi_type;
    using card_t  = typename P::cardinal_type;
    using value_t = typename P::value_type;

    using sub_t = as_wide_t<value_t, typename card_t::split_type>;

    if constexpr( is_emulated_v<abi_t> )
    {
      auto eval = [&](auto... I) { return sub_t {a.get(I + (Slice::value * sub_t::static_size))...}; };

      return apply<card_t::value / 2>(eval);
    }
    else if constexpr( is_aggregated_v<abi_t> )
    {
      return a.storage().segments[Slice::value];
    }
  }

  //================================================================================================
  // Logical slices
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(logical<wide<T, N>> const &a) noexcept
  {
    if constexpr( is_native_v<abi_t<T, N>> )
    {
      using l_t   = logical<wide<T, typename N::split_type>>;
      using s_t   = typename l_t::storage_type;
      using t_t   = std::array<l_t, 2>;
      auto [l, h] = a.mask().slice();
      return t_t{ l_t( bit_cast(l.storage(), as_<s_t>()) )
                , l_t( bit_cast(h.storage(), as_<s_t>()) )
                };
    }
    else
    {
      return slice_impl(a);
    }
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(logical<wide<T, N>> const &a, Slice const &s) noexcept
  {
    if constexpr( is_native_v<abi_t<T, N>> )
    {
      using l_t = logical<wide<T, typename N::split_type>>;
      using s_t = typename l_t::storage_type;
      return l_t( bit_cast(a.mask().slice(s).storage(), as_<s_t>()) );
    }
    else
    {
      return slice_impl(a, s);
    }
  }

  //================================================================================================
  // Arithmetic slices
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N> const &a) noexcept
      requires non_native_abi<abi_t<T, N>>
  {
    return slice_impl(a);
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N> const &a, Slice const &s) noexcept
      requires non_native_abi<abi_t<T, N>>
  {
    return slice_impl(a, s);
  }
}
