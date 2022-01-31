//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/product_type.hpp>

#include <eve/module/core/detail/basic_shuffle.hpp>

#include <eve/function/combine.hpp>

namespace eve::detail
{
  //==============================================================================================
  // Classify a pattern as a deinterleave_groups
  template<std::ptrdiff_t... I> inline constexpr auto is_deinterleave_groups_shuffle = []()
  {
    // List all possible patterns for a current size
    constexpr auto sz = sizeof...(I);
    constexpr auto x = []<std::size_t... N>( std::index_sequence<N...> )
    {
      return kumi::make_tuple(deinterleave_groups_shuffle_pattern<sz/(1<<(N+1)),sz>... );
    }(std::make_index_sequence<std::bit_width(sz)-1>{});

    // Find the fitting one
    constexpr auto idx = detail::find_index(pattern<I...>,x);
    return fixed<sz/(1<<(idx+1))>{};
  }();

  template<typename T, typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE
  auto deinterleave_groups_shuffle_as_doubles(wide<T, N> v, fixed<G>)
  {
    using doubles = wide<double, fixed<N() * sizeof(T) / 8>>;

    auto cast_v = bit_cast(v, eve::as<doubles>{});

    auto res = deinterleave_groups_shuffle(cast_v, lane<G * sizeof(T) / 8>);

    return bit_cast(res, as(v));
  }

  template<typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE
  auto deinterleave_groups_shuffle_as_doubles(wide<float, N> v0, wide<float, N> v1, fixed<G>)
  {
    using doubles = wide<double, typename N::split_type>;

    auto cast_v0 = bit_cast(v0, eve::as<doubles>{});
    auto cast_v1 = bit_cast(v1, eve::as<doubles>{});

    auto res = deinterleave_groups_shuffle(cast_v0, cast_v1, lane<G / 2>);

    return bit_cast(res, as<wide<float, typename N::combined_type>>{});
  }

  template<typename T, typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE
  auto deinterleave_groups_shuffle_(EVE_SUPPORTS(cpu_), wide<T, N> v, fixed<G>)
    requires (G <= N())
  {
         if constexpr ( G >= N() / 2                     ) return v;
    else if constexpr ( has_aggregated_abi_v<wide<T, N>> )
    {
      auto [v0,v1] = v.slice();
      return deinterleave_groups_shuffle(v0, v1, lane<G>);
    }
    else if constexpr( is_bundle_v<abi_t<T, N>>  )
    {
      return wide<T, N>( kumi::map([](auto _v) { return deinterleave_groups_shuffle(_v, lane<G>); }, v));
    }
    else
    {
      return basic_shuffle(v, deinterleave_groups_shuffle_pattern<G, N{}()>);
    }
  }

  template<typename T, typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE
  auto deinterleave_groups_shuffle_(EVE_SUPPORTS(cpu_), wide<T, N> v0, wide<T, N> v1, fixed<G>)
    requires (G <= N() * 2)
  {
    using res_t = wide<T, typename N::combined_type>;

         if constexpr ( G       >= N()                    ) return eve::combine(v0, v1);
    else if constexpr ( is_bundle_v<abi_t<T, N>>          )
    {
      return res_t(kumi::map([](auto _v0, auto _v1) { return deinterleave_groups_shuffle(_v0, _v1, lane<G>); }
                , v0, v1));
    }
    else if constexpr ( !has_emulated_abi_v<wide<T, N>> && G == (N() / 2)  )
    {
      auto [a0, b0] = v0.slice();
      auto [a1, b1] = v1.slice();
      v0 = eve::combine(a0, a1);
      v1 = eve::combine(b0, b1);
      return eve::combine(v0, v1);
    }
    else if constexpr ( !has_emulated_abi_v<wide<T, N>> )
    {
      v0 = deinterleave_groups_shuffle(v0, lane<G>);
      v1 = deinterleave_groups_shuffle(v1, lane<G>);
      return deinterleave_groups_shuffle(v0, v1, lane<N() / 2>);
    }
    else
    {
      res_t r;

      int o = 0;

      // Set first half
      for (int i = 0; i != N(); i += 2 * G) {
        for (int j = 0; j != G; ++j) r.set(o++, v0.get(i + j));
      }
      for (int i = 0; i != N(); i += 2 * G) {
        for (int j = 0; j != G; ++j) r.set(o++, v1.get(i + j));
      }

      // Set second half
      for (int i = 0; i != N(); i += 2 * G) {
        for (int j = 0; j != G; ++j) r.set(o++, v0.get(i + j + G));
      }
      for (int i = 0; i != N(); i += 2 * G) {
        for (int j = 0; j != G; ++j) r.set(o++, v1.get(i + j + G));
      }

      return r;
    }

  }
}
