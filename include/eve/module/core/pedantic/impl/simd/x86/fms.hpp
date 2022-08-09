//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                fms_(EVE_SUPPORTS(avx2_),
                     pedantic_type const&,
                     wide<T, N> const                &a,
                     wide<T, N> const                &b,
                     wide<T, N> const                &c) noexcept requires x86_abi<abi_t<T, N>>
{
  if constexpr( supports_fma3 ) { return fms(a, b, c); }
  else { return fms_(EVE_RETARGET(cpu_), pedantic_type(), a, b, c); }
}
}
