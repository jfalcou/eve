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
  struct bit_cast_t : callable<bit_cast_t, Options>
  {
    template<typename T, typename Target>
    requires (sizeof(T) == sizeof(Target))
    EVE_FORCEINLINE constexpr Target operator()(T const& a, as<Target> const& tgt) const noexcept
    {
      return EVE_DISPATCH_CALL(a,tgt);
    }

    EVE_CALLABLE_OBJECT(bit_cast_t, bit_cast_);
  };

  inline constexpr auto bit_cast = functor<bit_cast_t>;
}

#include <eve/detail/function/simd/common/bit_cast.hpp>

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/bit_cast.hpp>
#endif
