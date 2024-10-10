//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<callable_options O, logical_simd_value T, logical_simd_value U>
  EVE_FORCEINLINE constexpr U simd_cast_(EVE_REQUIRES(avx512_), O const&, T x, as<U>)
    requires (!has_aggregated_abi_v<T> && !has_aggregated_abi_v<U>)
  {
    using s_t = typename U::storage_type;
    return s_t {static_cast<typename s_t::type>(x.storage().value)};
  }
}
