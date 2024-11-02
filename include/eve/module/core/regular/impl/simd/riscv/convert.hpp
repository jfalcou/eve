//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/riscv/rvv_utils.hpp>
#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{

template<value In, scalar_value Out>
EVE_FORCEINLINE auto
convert_impl(EVE_REQUIRES(rvv_), logical<In> v, as<logical<Out>> tgt) noexcept
requires rvv_abi<typename In::abi_type>
{
  using out_t = as_wide_t<logical<Out>, cardinal_t<In>>;
  return simd_cast(v, as<out_t> {});
}

}
