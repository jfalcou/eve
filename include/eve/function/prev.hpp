//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/assert.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct prev_; }

  namespace detail
  {

    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::prev_), T const&, [[ maybe_unused ]] U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::prev] : second parameter must be positive");
    }

    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::prev_), T const&,[[ maybe_unused ]]  U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[[eve::saturated([eve::prev)] : second parameter must be positive");
    }
  }

  EVE_MAKE_CALLABLE(prev_, prev);
}

#include <eve/module/real/core/function/regular/generic/prev.hpp>
