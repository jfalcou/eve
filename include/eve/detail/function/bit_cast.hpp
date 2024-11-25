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
    EVE_FORCEINLINE constexpr Target operator()(T const& a, as<Target> tgt) const noexcept
      requires (sizeof(T) == sizeof(Target))
    {
      return this->behavior(as<Target>{}, eve::current_api, this->options(), a, tgt);
    }

    EVE_CALLABLE_OBJECT(bit_cast_t, bit_cast_);
  };

  inline constexpr auto bit_cast = functor<bit_cast_t>;
}

#include <eve/detail/function/simd/common/bit_cast.hpp>

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/detail/function/simd/arm/sve/bit_cast.hpp>
#endif
