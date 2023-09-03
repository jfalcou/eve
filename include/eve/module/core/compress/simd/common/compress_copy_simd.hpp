//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/compress/compress_store.hpp>

namespace eve
{

struct compress_copy_simd_core
{
  template<typename Settings, typename I, logical_simd_value L, typename O>
  EVE_FORCEINLINE auto operator()(Settings settings, I f, L m, O o) const -> unaligned_t<O>
  {
    return operator()(settings, f, eve::load[settings.c_in](f, typename L::cardinal_type {}), m, o);
  }

  template<typename Settings, typename I, logical_simd_value L, typename O>
  EVE_FORCEINLINE auto operator()(Settings settings,
                                  I,
                                  as_wide_t<value_type_t<I>, typename L::cardinal_type> preloaded,
                                  L                                                     m,
                                  O o) const -> unaligned_t<O>
  {
    return compress_store[settings.safety][settings.c_in][settings.c_out](preloaded, m, o);
  }
};

inline constexpr auto compress_copy_simd = detail::compress_callable<compress_copy_simd_core> {};

}
