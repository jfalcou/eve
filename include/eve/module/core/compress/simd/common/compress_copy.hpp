//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/compress/detail/compress_callable.hpp>
#include <eve/module/core/compress/detail/compress_copy_scalar.hpp>

#include <string>

namespace eve
{

struct compress_copy_core
{
  template<typename Settings, typename I, logical_simd_value L, typename O>
  EVE_FORCEINLINE auto operator()(Settings settings, I f, L m, O o_) const -> unaligned_t<O>
  {
    using CIn  = typename Settings::cond_in_t;
    using COut = typename Settings::cond_out_t;

    auto o = eve::unalign(o_);

    if constexpr( CIn::is_complete && !CIn::is_inverted ) return o;
    else if constexpr( COut::is_complete && !COut::is_inverted ) return o;
    else if constexpr( !Settings::is_safe && !CIn::is_complete && !COut::is_complete )
    {
      auto settings2 = detail::compress_callable_settings{safe, settings.density, settings.c_in, settings.c_out};
      return operator()(settings2, f, m, o);
    }
    else return detail::compress_copy_scalar(settings, f, m, o);
  }

  template<typename Settings, typename I, logical_simd_value L, typename O>
  EVE_FORCEINLINE auto operator()(Settings                                              settings,
                                  I                                                     f,
                                  as_wide_t<value_type_t<I>, typename L::cardinal_type> preloaded,
                                  L                                                     m,
                                  O o_) const -> unaligned_t<O>
  {
    using CIn  = typename Settings::cond_in_t;
    using COut = typename Settings::cond_out_t;

    (void) preloaded;

    auto o = eve::unalign(o_);

    if constexpr( CIn::is_complete && !CIn::is_inverted ) return o;
    else if constexpr( COut::is_complete && !COut::is_inverted ) return o;
    else if constexpr( !Settings::is_safe && !CIn::is_complete && !COut::is_complete )
    {
      auto settings2 = detail::compress_callable_settings{safe, settings.density, settings.c_in, settings.c_out};
      return operator()(settings2, f, m, o);
    }
    else return detail::compress_copy_scalar(settings, f, m, o);
  }
};

inline auto compress_copy = detail::compress_callable<compress_copy_core> {};

}
