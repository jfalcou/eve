//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/unalign.hpp>

#include <algorithm>
#include <type_traits>

EVE_NAMESPACE::_
{
  // Do not fold these calls into the overloaded svunpklo: clang rejects it on a fixed-length
  // svuint8_t as ambiguous with svunpklo(svbool_t)
  template<bool High, typename T, width_type N>
  auto sve_unpack(wide<T, N> v) noexcept
  {
    auto r = v.storage();

    if constexpr( std::is_signed_v<T> )
    {
      if      constexpr( sizeof(T) == 1 ) return High ? svunpkhi_s16(r) : svunpklo_s16(r);
      else if constexpr( sizeof(T) == 2 ) return High ? svunpkhi_s32(r) : svunpklo_s32(r);
      else                                return High ? svunpkhi_s64(r) : svunpklo_s64(r);
    }
    else
    {
      if      constexpr( sizeof(T) == 1 ) return High ? svunpkhi_u16(r) : svunpklo_u16(r);
      else if constexpr( sizeof(T) == 2 ) return High ? svunpkhi_u32(r) : svunpklo_u32(r);
      else                                return High ? svunpkhi_u64(r) : svunpklo_u64(r);
    }
  }

  template<typename U, typename T, width_type N>
  wide<U, N> sve_widen(wide<T, N> v) noexcept
  {
    if constexpr( sizeof(T) == sizeof(U) ) return bit_cast(v, as<wide<U, N>>{});
    else if constexpr( aggregated_abi<wide<T, N>> )
    {
      auto [l, h] = v.slice();
      return wide<U, N>{sve_widen<U>(l), sve_widen<U>(h)};
    }
    else
    {
      using s_t = std::conditional_t<std::is_signed_v<T>, signed, unsigned>;
      using h_t = make_integer_t<2 * sizeof(T), s_t>;

      if constexpr( aggregated_abi<wide<h_t, N>> )
      {
        using half_t = wide<h_t, N / 2>;
        auto lo      = half_t{sve_unpack<false>(v)};
        auto hi      = half_t{sve_unpack<true>(v)};
        return sve_widen<U>(wide<h_t, N>{lo, hi});
      }
      else return sve_widen<U>(wide<h_t, N>{sve_unpack<false>(v)});
    }
  }

  template<typename U, typename T, width_type N>
  logical<wide<U, N>> sve_widen(logical<wide<T, N>> m) noexcept
  {
    if constexpr( sizeof(T) == sizeof(U) ) return m;
    else if constexpr( aggregated_abi<wide<T, N>> )
    {
      auto [l, h] = m.slice();
      return logical<wide<U, N>>{sve_widen<U>(l), sve_widen<U>(h)};
    }
    else
    {
      using h_t = make_integer_t<2 * sizeof(T)>;

      if constexpr( aggregated_abi<wide<h_t, N>> )
      {
        using half_t = logical<wide<h_t, N / 2>>;
        auto lo      = half_t{svunpklo_b(m.storage())};
        auto hi      = half_t{svunpkhi_b(m.storage())};
        return sve_widen<U>(logical<wide<h_t, N>>{lo, hi});
      }
      else return sve_widen<U>(logical<wide<h_t, N>>{svunpklo_b(m.storage())});
    }
  }

  template<typename E, typename U, typename I, width_type N>
  void sve_scatter_truncated(E* p, logical<wide<U, N>> m, wide<U, N> d, wide<I, N> i) noexcept
  {
    if constexpr( aggregated_abi<wide<U, N>> )
    {
      auto [ml, mh] = m.slice();
      auto [dl, dh] = d.slice();
      auto [il, ih] = i.slice();
      sve_scatter_truncated(p, ml, dl, il);
      sve_scatter_truncated(p, mh, dh, ih);
    }
    else
    {
      auto pm = m.storage();
      auto pi = i.storage();
      auto pd = d.storage();

      // svst1b has no index form, and a byte offset is the index of a 1-byte element
      if      constexpr( sizeof(E) == 1 ) svst1b_scatter_offset(pm, p, pi, pd);
      else if constexpr( sizeof(E) == 2 ) svst1h_scatter_index(pm, p, pi, pd);
      else                                svst1w_scatter_index(pm, p, pi, pd);
    }
  }

  template<typename T, width_type N, typename Idx, typename Ptr, callable_options O>
   void scatter_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> const& v, Ptr ptr, Idx const& idx) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    using i_t  = element_type_t<Idx>;
    using s_t  = std::conditional_t<std::is_signed_v<i_t>, signed, unsigned>;

    // SVE scatter instructions store 32- or 64-bit data with index of the same width
    constexpr auto lane = std::max({sizeof(T), sizeof(i_t), std::size_t{4}});

    if      constexpr( match_option<condition_key, O, ignore_all_> ) return;
    else if constexpr( aggregated_abi<wide<T, N>> )          scatter.behavior(cpu_{}, opts, v, ptr, idx);
    else if constexpr( sizeof(T) < lane )
    {
      using u_t = make_integer_t<sizeof(T)>;
      using w_t = make_integer_t<lane>;

      auto m = sve_widen<w_t>(expand_mask(opts[condition_key], as<wide<u_t, N>>{}));
      auto d = sve_widen<w_t>(bit_cast(v, as<wide<u_t, N>>{}));
      auto i = sve_widen<make_integer_t<lane, s_t>>(idx);
      sve_scatter_truncated(reinterpret_cast<u_t*>(unalign(ptr)), m, d, i);
    }
    else
    {
      auto m = expand_mask(opts[condition_key], as<wide<T, N>>{});
      svst1_scatter_index(m, unalign(ptr), sve_widen<make_integer_t<lane, s_t>>(idx), v);
    }
  }
}
