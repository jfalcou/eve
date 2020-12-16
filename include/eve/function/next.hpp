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
#include <eve/function/all.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/saturated.hpp>
#include <eve/concept/value.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  namespace tag { struct next_; }

  namespace detail
  {
    template<real_value T, integral_real_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::next_), T const&, [[ maybe_unused ]] U const & n)
    {
      EVE_ASSERT(all(is_gez(n)), "[eve::next] : second parameter must be positive");
    }

    template<real_value T, integral_real_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::next_), T const&,[[ maybe_unused ]]  U const & n)
    {
      EVE_ASSERT(all(is_gez(n)), "[eve::saturated(eve::next)] : second parameter must be positive");
    }
  }

  EVE_MAKE_CALLABLE(next_, next);
}

#include <eve/module/real/core/function/regular/generic/next.hpp>
