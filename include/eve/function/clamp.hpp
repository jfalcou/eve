//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/all.hpp>
#include <eve/assert.hpp>

namespace eve
{
  namespace tag { struct clamp_; }

  namespace detail
  {
    template<typename X, typename L, typename H>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::clamp_)
                              , X const&
                              , [[maybe_unused]] L const& lo
                              , [[maybe_unused]] H const& hi)
    {
      EVE_ASSERT(eve::all(lo <= hi), "[eve::clamp] Unordered clamp boundaries");
    }
  }
  EVE_MAKE_CALLABLE(clamp_, clamp);

}

#include <eve/module/real/core/function/regular/generic/clamp.hpp>
