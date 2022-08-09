//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/add.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                fma_(EVE_SUPPORTS(vmx_),
                     pedantic_type const&,
                     wide<T, N> const                &v0,
                     wide<T, N> const                &v1,
                     wide<T, N> const                &v2) noexcept requires ppc_abi<wide<T, N>>
{
  if constexpr( std::is_floating_point_v<T> )
    return vec_madd(v0.storage(), v1.storage(), v2.storage());
  else return v0.storage() * v1.storage() + v2.storage();
}
}
