//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/implementation.hpp>

// byte_16_runtime_shuffle
// shuffle registers of bytes with len <= 16 using runtime idxs
// Not avaliable well on all platforms ==> declared in detail

namespace eve
{
  EVE_REGISTER_CALLABLE(byte_16_runtime_shuffle_)
  EVE_DECLARE_CALLABLE(byte_16_runtime_shuffle_, byte_16_runtime_shuffle)

  namespace detail
  {
    EVE_ALIAS_CALLABLE(byte_16_runtime_shuffle_, byte_16_runtime_shuffle);
  }

  EVE_CALLABLE_API(byte_16_runtime_shuffle_, byte_16_runtime_shuffle)
}

#include <eve/detail/function/simd/common/byte_16_runtime_shuffle.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/byte_16_runtime_shuffle.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/byte_16_runtime_shuffle.hpp>
#endif
