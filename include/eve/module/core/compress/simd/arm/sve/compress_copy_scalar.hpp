//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/logical_andnot.hpp>

namespace eve::detail
{

template <typename I, typename L, typename O>
EVE_FORCEINLINE O
compress_copy_sparse_sve_no_limits(I f, L m, O o)
{
  if constexpr( has_aggregated_abi_v<L> )
  {
    auto [lo, hi] = m.slice();
    o             = compress_copy_sparse_sve_no_limits(f, lo, o);
    return compress_copy_sparse_sve_no_limits(f + (L::size() / 2), hi, o);
  }
  else
  {
    while( any(m) )
    {
      L ignored_before = svbrka_z(sve_true<element_type_t<L>>(), m);
      m = svbic_z(sve_true<element_type_t<L>>(), m, ignored_before);
      auto cur = f + count_true(ignored_before) - 1;
      eve::write(eve::read(cur), o++);
    }
    return o;
  }
}

template <typename I, typename L, typename O>
EVE_FORCEINLINE O
compress_copy_sparse_sve_limited(I f, L m, O o, O limit)
{
  if constexpr( has_aggregated_abi_v<L> )
  {
    auto [lo, hi] = m.slice();
    o             = compress_copy_sparse_sve_limited(f, lo, o, limit);
    return compress_copy_sparse_sve_limited(f + (L::size() / 2), hi, o, limit);
  }
  else
  {
    while( any(m) )
    {
      if (o == limit) return o;
      L ignored_before = svbrka_z(sve_true<element_type_t<L>>(), m);
      m = svbic_z(sve_true<element_type_t<L>>(), m, ignored_before);
      auto cur = f + count_true(ignored_before) - 1;
      eve::write(eve::read(cur), o++);
    }
    return o;
  }
}

template<typename Settings, typename I, typename L, typename O>
EVE_FORCEINLINE auto
compress_copy_scalar_impl_(EVE_SUPPORTS(sve_), Settings settings, I f, L m, O o) -> O
    requires(Settings::is_sparse) //
{
  using IC = typename Settings::cond_in_t;
  using OC = typename Settings::cond_out_t;

  if constexpr( L::size() < 4 )
  {
    return compress_copy_scalar_impl(
        compress_callable_settings(settings.safety, dense, settings.c_in, settings.c_out), f, m, o);
  }
  else if constexpr( !IC::is_complete )
  {
    return compress_copy_scalar_impl(
        compress_callable_settings(settings.safety, settings.density, ignore_none, settings.c_out),
        f,
        m && to_logical(settings.c_in, as{m}),
        o);
  }
  else if constexpr ( !OC::is_complete )
  {
    o += settings.c_out.offset(eve::as{m});
    O limit = o + settings.c_out.count(eve::as{m});
    return compress_copy_sparse_sve_limited(f, m, o, limit);
  }
  else
  {
    return compress_copy_sparse_sve_no_limits(f, m, o);
  }
}

}
