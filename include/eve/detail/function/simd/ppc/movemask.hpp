//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/logical.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <utility>

namespace eve::detail
{
  // Adapted from this completely unsuspecting thread:
  // https://stackoverflow.com/questions/33938584/on-powerpc-is-there-any-equivalent-of-intels-movemask-intrinsics
  template<arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE
  std::pair<std::uint64_t,fixed<1>> movemask(logical<wide<T, N>> const &v) noexcept requires ppc_abi<abi_t<T, N>>
  {
    using vu8 = typename wide<T,N>::template rebind<std::uint8_t>;
    vu8 mask([](auto i, auto c)
    {
      constexpr auto spacing = sizeof(T)*8;
      // Any value above 128 means 0 so this always work without checking if i is above or below N
      return (c-1-i) * spacing;
    });

    auto result = vec_vbpermq(bit_cast(v.bits(),as(mask)).storage(), mask.storage());
    return {result[0], eve::lane<1>};
  }
}
