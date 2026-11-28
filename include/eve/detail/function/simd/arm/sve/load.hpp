//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/intrinsic_wrappers/arm/arm_utils.hpp>
#include <eve/detail/intrinsic_wrappers/arm/sve/sve_true.hpp>
#include <eve/module/core/regular/unalign.hpp>

EVE_NAMESPACE::_
{
  template<typename T, width_type N, simd_compatible_ptr<wide<T, N>> Ptr>
  wide<T, N> load_impl(sve_, Ptr p, as<wide<T, N>> tgt) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return svld1(ignore_none.mask(tgt), arm_ptr_downcast(unalign(p)));
  }

  template<typename T, width_type N, typename Alt>
  wide<T, N> load_masked_impl(sve_, logical<wide<T, N>> m, Alt alt, T const* p, as<wide<T, N>>) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    wide<T, N> res = svld1(m, arm_ptr_downcast(p));

    if constexpr (std::same_as<Alt, wide<T, N>>) return if_else(m, res, alt);
    else                                         return res;
  }
}
