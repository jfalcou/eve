//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <type_traits>

namespace eve
{
  namespace tag
  {
    struct sqrt_;
  }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::sqrt_), [[maybe_unused]] T const &v)
    {
      if constexpr( std::is_integral_v<T> && std::is_signed_v<T> )
      {
        EVE_ASSERT(v >= 0, "[eve::sqrt] - Invalid parameter: " << v);
      }
    }
  }

  EVE_MAKE_CALLABLE(sqrt_, sqrt);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/regular/generic/sqrt.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/regular/simd/x86/sqrt.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/regular/simd/ppc/sqrt.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/regular/simd/arm/neon/sqrt.hpp>
#endif
