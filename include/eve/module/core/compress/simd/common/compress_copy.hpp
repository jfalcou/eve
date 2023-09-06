//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/compress/compress_copy_scalar.hpp>
#include <eve/module/core/compress/compress_copy_simd.hpp>
#include <eve/module/core/compress/detail/compress_callable.hpp>

namespace eve
{

struct compress_copy_core
{
  template<typename Settings, typename L> static constexpr auto select_strategy(as<Settings>, as<L>)
  {
    using COut = typename Settings::cond_out_t;
    if constexpr( eve::has_emulated_abi_v<L> ) return compress_copy_scalar;
    else if constexpr( eve::current_api >= sve || eve::current_api >= avx512 )
      return compress_copy_simd;
    else if constexpr( Settings::is_sparse || !COut::is_complete ) return compress_copy_scalar;
    else return compress_copy_simd;
  }

  template<typename Settings, typename I, logical_simd_value L, typename O>
  EVE_FORCEINLINE auto operator()(Settings settings, I f, L m, O o) const -> unaligned_t<O>
  {
    constexpr auto impl = select_strategy(as<Settings> {}, as<L> {});
    return impl[settings.safety][settings.density][settings.c_in][settings.c_out](f, m, o);
  }

  template<typename Settings, typename I, logical_simd_value L, typename O>
  EVE_FORCEINLINE auto operator()(Settings                                              settings,
                                  I                                                     f,
                                  as_wide_t<value_type_t<I>, typename L::cardinal_type> preloaded,
                                  L                                                     m,
                                  O o) const -> unaligned_t<O>
  {
    constexpr auto impl = select_strategy(as<Settings> {}, as<L> {});
    return impl[settings.safety][settings.density][settings.c_in][settings.c_out](
        f, preloaded, m, o);
  }
};

inline constexpr auto compress_copy = detail::compress_callable<compress_copy_core> {};

}
