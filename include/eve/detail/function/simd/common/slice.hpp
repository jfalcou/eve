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
#include <eve/detail/function/bit_cast.hpp>
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
  //! @addtogroup utility
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
      auto eval = [&](auto... I) { return sub_t {a.get(I + (Slice::value * sub_t::size()))...}; };

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
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto slice(logical<wide<T, N, ABI>> const &a) noexcept
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

  template<typename T, typename N, typename ABI, typename Slice>
  EVE_FORCEINLINE auto slice(logical<wide<T, N, ABI>> const &a, Slice const &s) noexcept
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
  template<typename T, typename N, non_native_abi ABI>
  EVE_FORCEINLINE auto slice(wide<T, N, ABI> const &a) noexcept
  {
    return slice_impl(a);
  }

  template<typename T, typename N, non_native_abi ABI, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, ABI> const &a, Slice const &s) noexcept
  {
    return slice_impl(a, s);
  }
}
