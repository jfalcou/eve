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
#include <eve/function/is_flint.hpp>
#include <eve/function/all.hpp>

namespace eve
{
  namespace tag { struct ldexp_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::ldexp_), T const&, [[maybe_unused]]  U const& b)
    {
      if constexpr(std::is_floating_point_v<value_type_t<U>>)
        EVE_ASSERT(all(is_flint(b)), "[eve::ldexp] argument 2 is floating but not a flint");
    }

    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::ldexp_), pedantic_type const&, T const&,  [[maybe_unused]] U const& b)
    {
      if constexpr(std::is_floating_point_v<value_type_t<U>>)
        EVE_ASSERT(all(is_flint(b)), "ldexp argument 2 is floating but not a flint");
    }
  }

  EVE_MAKE_CALLABLE(ldexp_, ldexp);
}

#include <eve/module/core/function/regular/generic/ldexp.hpp>
