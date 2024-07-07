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
  struct slice_callable_t : callable<slice_callable_t, Options>
  {
    template<typename T, typename Target>
    requires (sizeof(T) == sizeof(Target))
    EVE_FORCEINLINE constexpr Target operator()(T const& a, as<Target> const& tgt) const noexcept
    {
      return EVE_DISPATCH_CALL(a,tgt);
    }

    EVE_CALLABLE_OBJECT(slice_callable_t, slice_);
  };

  inline constexpr auto slice = functor<slice_callable_t>;
}

#include <eve/detail/function/simd/common/slice.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/slice.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/slice.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/slice.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/slice.hpp>
#endif
