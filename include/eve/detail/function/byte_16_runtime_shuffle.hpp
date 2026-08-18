//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
  template<typename Options>
  struct byte_16_runtime_shuffle_t : callable<byte_16_runtime_shuffle_t, Options>
  {
    template<typename N>
    EVE_FORCEINLINE wide<std::uint8_t, N> operator()(
        wide<std::uint8_t, N> what, 
        wide<std::uint8_t, N> pattern) const noexcept
    {
      return EVE_DISPATCH_CALL(what, pattern);
    }

    EVE_CALLABLE_OBJECT(byte_16_runtime_shuffle_t, byte_16_runtime_shuffle_);
  };

  inline constexpr auto byte_16_runtime_shuffle = functor<byte_16_runtime_shuffle_t>;
}

#include <eve/detail/function/simd/common/byte_16_runtime_shuffle.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/byte_16_runtime_shuffle.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/detail/function/simd/arm/neon/byte_16_runtime_shuffle.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/byte_16_runtime_shuffle.hpp>
#endif
