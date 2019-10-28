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

#include <eve/detail/is_native.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/platform.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <cstddef>

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
  //------------------------------------------------------------------------------------------------
  // Full slice
  template<typename P>
  EVE_FORCEINLINE auto slice_impl(P const &a) noexcept
  {
    using abi_t   = typename P::abi_type;
    using card_t  = typename P::cardinal_type;
    using value_t = typename P::value_type;

    using sub_t = as_wide_t<value_t, typename card_t::split_type>;

    if constexpr(is_emulated_v<abi_t>)
    {
      auto eval = [&](auto... I)
      {
        using that_t = std::array<sub_t, 2>;
        return that_t{sub_t{a[ I ]...}, sub_t{a[ I + card_t::value / 2 ]...}};
      };

      return apply<card_t::value / 2>(eval);
    }
    else if constexpr(is_aggregated_v<abi_t>)
    {
      std::array<sub_t, 2> that{ a.slice(lower_), a.slice(upper_)};
      return that;
    }
    else
    {
      static_assert(wrong<abi_t>, "[eve::slice(a) - Unsupported SIMD ABI");
    }
  }

  //------------------------------------------------------------------------------------------------
  // Partial slice
  template<typename P, typename Slice>
  EVE_FORCEINLINE auto slice_impl(P const &a, Slice const &) noexcept
  {
    using abi_t   = typename P::abi_type;
    using card_t  = typename P::cardinal_type;
    using value_t = typename P::value_type;

    using sub_t = as_wide_t<value_t, typename card_t::split_type>;

    if constexpr(is_emulated_v<abi_t>)
    {
      auto eval = [&](auto... I)
      {
        return sub_t{a[ I + (Slice::value * sub_t::static_size) ]...};
      };

      return apply<card_t::value / 2>(eval);
    }
    else if constexpr(is_aggregated_v<abi_t>)
    {
      static constexpr auto reps = P::storage_type::replication;

      if constexpr(reps == 2)
      {
        return a.storage().segments[Slice::value];
      }
      else
      {
        sub_t that;
        static constexpr auto subreps = sub_t::storage_type::replication;
        static constexpr auto offset  = Slice::value*subreps;

        auto const& out = a.storage().segments;
        detail::apply<subreps>( [&](auto const&... I)
                                {
                                  that.storage().segments = { out[I + offset]... };
                                }
                              );

        return that;
      }
    }
    else
    {
      static_assert(wrong<abi_t>, "[eve::slice(a,s) - Unsupported SIMD ABI");
    }
  }

  //------------------------------------------------------------------------------------------------
  // Mapping over wide-like type
template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE std::array<logical<wide<T, typename N::split_type>>, 2>
                  slice(logical<wide<T, N, ABI>> const &a) noexcept
  {
    if constexpr( is_native_v<ABI> )
    {
      using l_t     = logical<wide<T, typename N::split_type>>;
      using t_t     = std::array<l_t, 2>;
      auto [ l, h ] = a.bits().slice();
      return t_t{l_t(l.storage(), eve::from_bits), l_t(h.storage(), eve::from_bits)};
    }
    else
    {
      return slice_impl(a);
    }
  }

  template<typename T, typename N, typename ABI, typename Slice>
  EVE_FORCEINLINE auto slice(logical<wide<T, N, ABI>> const &a, Slice const & s) noexcept
  {
    if constexpr( is_native_v<ABI> )
    {
      using l_t = logical<wide<T, typename N::split_type>>;
      return l_t(a.bits().slice(s).storage(), eve::from_bits);
    }
    else
    {
      return slice_impl(a,s);
    }
  }

  //------------------------------------------------------------------------------------------------
  // Arithmetic full slice
  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto slice(wide<T, N, ABI> const &a) noexcept
  {
    return slice_impl(a);
  }

  //------------------------------------------------------------------------------------------------
  // Arithmetic partial slice
  template<typename T, typename N, typename ABI, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, ABI> const &a, Slice const & s) noexcept
  {
    return slice_impl(a,s);
  }
}

#endif
