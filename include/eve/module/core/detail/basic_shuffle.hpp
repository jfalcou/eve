//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

namespace eve
{
EVE_REGISTER_CALLABLE(basic_shuffle_)
EVE_DECLARE_CALLABLE(basic_shuffle_, basic_shuffle)

namespace detail
{
  EVE_ALIAS_CALLABLE(basic_shuffle_, basic_shuffle);
}

EVE_CALLABLE_API(basic_shuffle_, basic_shuffle)
}

#include <eve/module/core/detail/generic/basic_shuffle.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/detail/simd/x86/basic_shuffle.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/detail/simd/ppc/basic_shuffle.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/detail/simd/arm/neon/basic_shuffle.hpp>
#endif
