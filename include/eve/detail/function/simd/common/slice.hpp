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
    using l_t     = logical<wide<T, typename N::split_type>>;
    using t_t     = std::array<l_t, 2>;
    auto [ l, h ] = a.bits().slice();
    return t_t{l_t(l.storage(), eve::from_bits), l_t(h.storage(), eve::from_bits)};
  }

  template<typename T, typename N, typename Arch, typename Slice>
  EVE_FORCEINLINE logical<wide<T, typename N::split_type>> slice(logical<wide<T, N, Arch>> const &a,
                                                                 Slice const &s) noexcept
  {
    using l_t = logical<wide<T, typename N::split_type>>;
    auto sa   = a.bits().slice(s);
    return l_t(sa.storage(), eve::from_bits);
  }

  //------------------------------------------------------------------------------------------------
  // Arithmetic full slice
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto slice(wide<T, N, ABI> const &a) noexcept
  {
    if constexpr(is_emulated_v<ABI>)
    {
      auto eval = [&](auto... I) {
        using wide_t = wide<T, typename N::split_type>;
        using that_t = std::array<wide_t, 2>;
        return that_t{wide_t{a[ I ]...}, wide_t{a[ I + N::value / 2 ]...}};
      };

      return apply<N::value / 2>(eval);
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
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
      {
        return a.storage();
      }
    }
    else
    {
      static_assert(wrong<ABI>, "[eve::slice(a) - Unsupported SIMD ABI");
    }
  }

  //------------------------------------------------------------------------------------------------
  // Arithmetic partial slice
  template<typename T, typename N, typename ABI, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, ABI> const &a, Slice const &) noexcept
  {
    if constexpr(is_emulated_v<ABI>)
    {
      auto eval = [&](auto... I) {
        return wide<T, typename N::split_type>{a[ I + (Slice::value * N::value / 2) ]...};
      };

      return apply<N::value / 2>(eval);
    }
    else if constexpr(is_aggregated_v<ABI>)
    {
      if constexpr(Slice::value == 0)
        return a.storage().lo;
      else
        return a.storage().hi;
    }
    else
    {
      static_assert(wrong<ABI>, "[eve::slice(a,s) - Unsupported SIMD ABI");
    }
  }
}

#endif
