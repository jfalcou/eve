//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/is_flint.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE void check( EVE_SUPPORTS(eve::tag::ldexp_)
                            , eve::pedantic_type const &, T const&
                            , [[maybe_unused]]  U const& b
                            )
  {
    if constexpr(std::is_floating_point_v<element_type_t<U>>)
      EVE_ASSERT( eve::all(is_flint(b))
                , "[eve::pedantic(eve::ldexp)] argument 2 is floating but not a flint"
                );
  }
}

#include <eve/module/core/pedantic/impl/ldexp.hpp>
