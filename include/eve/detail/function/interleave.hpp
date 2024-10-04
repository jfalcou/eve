//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once


#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>

namespace eve
{
  template<typename Options>
  struct interleave_t : callable<interleave_t, Options>
  {
    template<eve::simd_value T, std::same_as<T>... Ts>
    EVE_FORCEINLINE kumi::tuple<T, Ts...> operator()(T v, Ts... vs) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((kumi::tuple<T, Ts...>), v, vs...);
    }

    template<simd_value T, std::same_as<T>... Ts>
    EVE_FORCEINLINE kumi::tuple<logical<T>, logical<Ts>...> operator()(logical<T> v, logical<Ts>... vs) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((kumi::tuple<logical<T>, logical<Ts>...>), v, vs...);
    }

    EVE_CALLABLE_OBJECT(interleave_t, interleave_);
  };

  inline constexpr auto interleave = functor<interleave_t>;
}

#include <eve/detail/function/simd/common/interleave.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/interleave.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/interleave.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/detail/function/simd/arm/neon/interleave.hpp>
#endif
