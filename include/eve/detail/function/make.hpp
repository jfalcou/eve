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
  struct make_t : callable<make_t, Options>
  {
    template<typename Target, typename... T>
    EVE_FORCEINLINE constexpr auto operator()(as<Target> tgt, T... vs) const noexcept
    {
      return EVE_DISPATCH_CALL(tgt, vs...);
    }

    EVE_CALLABLE_OBJECT(make_t, make_);
  };

  inline constexpr auto make = functor<make_t>;
}

#include <eve/detail/function/simd/common/make.hpp>

// #if defined(EVE_INCLUDE_X86_HEADER)
// #  include <eve/detail/function/simd/x86/make.hpp>
// #endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/make.hpp>
#endif
