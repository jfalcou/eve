//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/function/combine.hpp>

namespace eve::detail
{
template<callable_options O, typename T, typename Target>
EVE_FORCEINLINE constexpr Target
simd_cast_(EVE_REQUIRES(cpu_), O const&, T x, as<Target> tgt) noexcept
{
  if constexpr( product_simd_value<T> )
  {
    auto make_as       = []<typename M>(M) { return as<M> {}; };
    auto lifted_target = kumi::result::map_t<decltype(make_as), Target> {};
    return kumi::map(simd_cast, x, lifted_target);
  }
  else if constexpr( eve::has_emulated_abi_v<T> && eve::has_emulated_abi_v<Target> )
  {
    Target res;
    res.storage().fill(0);

    // Prevent g++ Wclass-memaccess warning when simd_casting emulated logical<wide>
    std::memcpy(reinterpret_cast<unsigned char*>(res.storage().data()),
                reinterpret_cast<unsigned char const*>(x.storage().data()),
                std::min(sizeof(typename T::storage_type), sizeof(typename Target::storage_type)));

    return res;
  }
  else if constexpr( sizeof(T) < sizeof(Target) ) { return simd_cast(combine(current_api, x, T{}), tgt); }
  else if constexpr( sizeof(T) > sizeof(Target) ) { return simd_cast(x.slice(lower_), tgt); }
  else { return bit_cast(x, tgt); }
}
}
