//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(broadcast_, broadcast);

  //================================================================================================
  // Premade pattern generator
  template<std::ptrdiff_t I, std::ptrdiff_t N>
  inline constexpr auto broadcast_n = fix_pattern<N>( [](auto, auto) { return I; } );

  namespace detail
  {
    //==============================================================================================
    // Detects <N,...,N> as a broadcast
    template<int I0, int... I> inline constexpr bool is_broadcast = ((I0 !=-1) && ... && (I0==I));
  }
}

#include <eve/detail/function/simd/common/broadcast.hpp>

#if defined(EVE_HW_POWERPC)
#  include <eve/detail/function/simd/ppc/broadcast.hpp>
#endif
