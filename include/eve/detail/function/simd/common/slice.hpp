//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_COMMON_SLICE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_COMMON_SLICE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <cstddef>
#include <iostream>

namespace eve
{
  struct upper_slice : std::integral_constant<std::size_t, 1>
  {
  };
  struct lower_slice : std::integral_constant<std::size_t, 0>
  {
  };

  inline constexpr upper_slice upper_ = {};
  inline constexpr lower_slice lower_ = {};
}

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Logical
  template<typename T, typename N, typename Arch>
  EVE_FORCEINLINE std::array<logical<wide<T, typename N::split_type>>, 2>
  slice(logical<wide<T, N, Arch>> const &a) noexcept
  {
    using l_t = logical<wide<T, typename N::split_type>>;
    using t_t = std::array<l_t, 2>;
    auto[l,h] = a.bits().slice();
    return t_t{ l_t(l.storage(),eve::from_bits), l_t(h.storage(),eve::from_bits)};
  }

  template<typename T, typename N, typename Arch, typename Slice>
  EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
  slice(logical<wide<T, N, Arch>> const &a, Slice const& s) noexcept
  {
    using l_t = logical<wide<T, typename N::split_type>>;
    auto sa = a.bits().slice(s);
    return l_t(sa.storage(),eve::from_bits);
  }

  //------------------------------------------------------------------------------------------------
  // Emulation
  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N, emulated_> const &a) noexcept
  {
    auto eval = [&](auto... I) {
      using wide_t = wide<T, typename N::split_type>;
      using that_t = std::array<wide_t, 2>;
      return that_t{wide_t{a[ I ]...}, wide_t{a[ I + N::value / 2 ]...}};
    };

    return apply<N::value / 2>(eval);
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, emulated_> const &a, Slice const &) noexcept
  {
    auto eval = [&](auto... I) {
      using wide_t = wide<T, typename N::split_type>;
      return wide_t{a[ I + (Slice::value * N::value / 2) ]...};
    };

    return apply<N::value / 2>(eval);
  }

  //------------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N, aggregated_> const &a) noexcept
  {
    // g++ has trouble returning the storage properly for large aggregate - we then copy it
    if constexpr(platform::compiler == compilers::gcc_ && sizeof(a) > 256)
    {
      auto eval = [&](auto... I) {
        using wide_t = wide<T, typename N::split_type>;
        using that_t = std::array<wide_t, 2>;
        return that_t{wide_t{a[ I ]...}, wide_t{a[ I + N::value / 2 ]...}};
      };

      return apply<N::value / 2>(eval);
    }
    else
      return a.storage();
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, aggregated_> const &a, Slice const &) noexcept
  {
    if constexpr(Slice::value == 0) return a.storage().lo;
    else                            return a.storage().hi;
  }
}

#endif
