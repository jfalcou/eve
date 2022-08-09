//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/product_type.hpp>
#include <eve/module/core/regular/deinterleave_groups_shuffle.hpp>
#include <eve/module/core/regular/swap_adjacent_groups.hpp>
#include <eve/module/core/regular/shuffle.hpp>

namespace eve::detail
{
  namespace _deinterleave_groups
  {
    template <std::size_t first, std::size_t step, kumi::product_type T>
    EVE_FORCEINLINE auto select_every_step_from_tuple(T t)
    {
      return [&]<std::size_t ...i>(std::index_sequence<i...>) {
        return kumi::reorder<(first + i * step)...>(t);
      }(std::make_index_sequence<std::tuple_size_v<T> / step>{});
    }

    template <std::ptrdiff_t G>
    struct recurse
    {
      EVE_FORCEINLINE auto operator()(auto ... x) const
      {
        return deinterleave_groups(lane<G>, x...);
      }
      EVE_FORCEINLINE auto operator()(kumi::product_type auto t) const
      {
        return kumi::apply(*this, t);
      }
    };

    template<std::ptrdiff_t G, typename T, typename... Ts>
    EVE_FORCEINLINE
    kumi::tuple<T, Ts...>
    emulate(eve::fixed<G>, T v0, Ts... vs)
    {
      auto const values = kumi::make_tuple(v0,vs...);
      constexpr std::size_t n_vs = sizeof...(Ts) + 1;

      constexpr auto prev_idx = [](std::size_t field_idx, std::size_t in_idx)
      {
        int group_in_field   = in_idx / G;
        int prev_group       = field_idx + group_in_field * n_vs;
        int idx_in_group     = in_idx % G;
        int prev_total       = prev_group * G + idx_in_group;

        return prev_total;
      };

      auto one_field = [&]<std::size_t field>(std::integral_constant<std::size_t, field>)
      {
        return [&]<std::size_t... in>(std::index_sequence<in...>) {
          return T { kumi::get<prev_idx(field, in) / T::size()>(values).get(prev_idx(field, in) % T::size())... };
        }(std::make_index_sequence<T::size()>{});
      };

      return [&]<std::size_t... fields>(std::index_sequence<fields...>)
      {
        return kumi::make_tuple(one_field(std::integral_constant<std::size_t, fields>{}) ...);
      }(std::make_index_sequence<n_vs> {});
    }
  }

  template<std::ptrdiff_t G, simd_value T, std::same_as<T>... Ts>
  EVE_FORCEINLINE
  kumi::tuple<T, Ts...>
  deinterleave_groups_(EVE_SUPPORTS(cpu_), eve::fixed<G> g, T v0, Ts... vs) noexcept
    requires ( T::size() >= G)
  {
    auto const values = kumi::make_tuple(v0,vs...);
    constexpr std::size_t n_vs      = sizeof...(Ts) + 1;
    constexpr std::size_t t_g_size  = T::size() / g;

         if constexpr ( n_vs == 1 || T::size() == G ) return values;
    else if constexpr ( has_emulated_abi_v<T>       ) return _deinterleave_groups::emulate(lane<G>, v0, vs...);
    else if constexpr ( n_vs == 2                   )
    {
      auto [l, h] = deinterleave_groups_shuffle(v0, get<1>(values), g).slice();
      return {l, h};
    }
    else if constexpr ( n_vs > t_g_size && (n_vs & 1) == 0 )  // we can select every other
    {
      auto even = _deinterleave_groups::select_every_step_from_tuple<0, 2>(values);
      auto odd  = _deinterleave_groups::select_every_step_from_tuple<1, 2>(values);
      _deinterleave_groups::recurse<G> r;

      return kumi::cat(r(even), r(odd));
    }
    else if constexpr ( T::size() == G ) return {v0, vs...};
    else if constexpr ( n_vs == 4 && !has_emulated_abi_v<T> )
    {
      T v1 = get<1>(values);
      T v2 = get<2>(values);
      T v3 = get<3>(values);

      // acac bdbd acac bdbd
      kumi::tie(v0, v1) = deinterleave_groups(g, v0, v1);
      kumi::tie(v2, v3) = deinterleave_groups(g, v2, v3);

      kumi::tie(v0, v2) = deinterleave_groups(g, v0, v2);
      kumi::tie(v1, v3) = deinterleave_groups(g, v1, v3);
      return {v0, v1, v2, v3};
    }
    else return _deinterleave_groups::emulate(lane<G>, v0, vs...);
  }
}
