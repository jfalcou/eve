//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
#include <eve/module/real/core/function/regular/generic/sqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/sqrt.hpp>
#endif
