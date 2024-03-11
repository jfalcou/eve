//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/native_shuffle_helpers.hpp>

namespace eve
{
EVE_REGISTER_CALLABLE(shuffle_l2_)
EVE_DECLARE_CALLABLE(shuffle_l2_, shuffle_l2)

namespace detail
{
  EVE_ALIAS_CALLABLE(shuffle_l2_, shuffle_l2);
} // namespace detail

// level 2 is allowed one instruction with no mask
EVE_CALLABLE_API(shuffle_l2_, shuffle_l2)
}

#include <eve/detail/shuffle_v2/simd/common/shuffle_l2.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/shuffle_v2/simd/x86/shuffle_l2.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/shuffle_v2/simd/arm/neon/shuffle_l2.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/detail/shuffle_v2/simd/arm/sve/shuffle_l2.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/shuffle_v2/simd/ppc/shuffle_l2.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/detail/shuffle_v2/simd/riscv/shuffle_l2.hpp>
#endif
