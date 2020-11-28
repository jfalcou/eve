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
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct shr_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::shr_), T const&, [[maybe_unused]] S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(s),
                  "[eve::shr] Shifting by " << s
                                            << " is out of the range [0, "
                                            << sizeof(value_type_t<T>) * 8
                                            << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(shr_, shr);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/regular/generic/shr.hpp>

#if defined(EVE_HW_X86)
#  include <eve/module/core/function/regular/simd/x86/shr.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/regular/simd/ppc/shr.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/module/core/function/regular/simd/arm/neon/shr.hpp>
#endif
