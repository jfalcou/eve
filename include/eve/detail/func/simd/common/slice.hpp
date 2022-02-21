//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/func/bit_cast.hpp>
#include <eve/platform.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/as.hpp>

#include <cstddef>
#include <type_traits>

namespace eve
{
  template<std::size_t Slice>
  struct  slice_t
        : std::integral_constant<std::size_t, Slice>
  {};

  using upper_slice_t = slice_t<1>;
  using lower_slice_t = slice_t<0>;

  //================================================================================================
  //! @addtogroup simd
  //! @{
  //================================================================================================
  //! @brief Tag to select the upper slice of a simd_value
  inline constexpr upper_slice_t const upper_ = {};

  //! @brief Tag to select the lower slice of a simd_value
  inline constexpr lower_slice_t const lower_ = {};
  //================================================================================================
  //! @}
  //================================================================================================
}

namespace eve::detail
{
  //================================================================================================
  // Full slice
  //================================================================================================
  template<typename P> EVE_FORCEINLINE auto slice_impl(P const &a) noexcept
  {
    using abi_t   = typename P::abi_type;

    if constexpr( is_aggregated_v<abi_t> )  return a.storage().segments;
    else                                    return std::array{a.slice(lower_), a.slice(upper_)};
  }

  //================================================================================================
  // Partial slice
  //================================================================================================
  template<typename P, typename Slice>
  EVE_FORCEINLINE auto slice_impl(P const &a, Slice const & s) noexcept
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
      return a.storage().segments[Slice::value];
    }
    else if constexpr( is_bundle_v<abi_t> )
    {
      return sub_t(kumi::map( [&](auto m) { return m.slice(s); }, a));
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
      return t_t{ l_t( bit_cast(l.storage(), as<s_t>()) )
                , l_t( bit_cast(h.storage(), as<s_t>()) )
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
      return l_t( bit_cast(a.mask().slice(s).storage(), as<s_t>()) );
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
