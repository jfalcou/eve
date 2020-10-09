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

#include <eve/assert.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  namespace tag
  {
    struct bit_shr_;
  }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void
    check(EVE_MATCH_CALL(eve::tag::bit_shr_), T const &, [[maybe_unused]] S const &s)
    {
      EVE_ASSERT(assert_good_shift<T>(s),
                 "[eve::bit_shr] Shifting by " << s << " is out of the range [0, "
                                               << sizeof(value_type_t<T>) * 8 << "[.");
    }
  }

  EVE_MAKE_CALLABLE(bit_shr_, bit_shr);
}

#include <eve/arch.hpp>
#include <eve/module/core/function/generic/bit_shr.hpp>

#if defined(EVE_HW_POWERPC)
#  include <eve/module/core/function/simd/ppc/bit_shr.hpp>
#endif
