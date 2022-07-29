//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/spy.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::detail
{

template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE wide<T, N>
                load_(EVE_SUPPORTS(sve_fixed_),
                      ignore_none_ const&,
                      safe_type const&,
                      eve::as<wide<T, N>> const&,
                      Ptr p) requires(sve_abi<abi_t<T, N>>)
{
  auto ptr = unalign(p);

  if constexpr( N() == expected_cardinal_v<T> ) return svld1(svptrue_b8(), ptr);
  else
  {
    typename wide<T, N>::storage_type that {};
    std::memcpy(&that, ptr, N::value * sizeof(T));
    return that;
  }
}

}
