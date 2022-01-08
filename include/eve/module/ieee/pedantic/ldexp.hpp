//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/pedantic.hpp>
#include <eve/module/ieee/regular/ldexp.hpp>

namespace eve
{
  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::ldexp_), pedantic_type const&, T const&,  [[maybe_unused]] U const& b)
    {
      if constexpr(std::is_floating_point_v<value_type_t<U>>)
        EVE_ASSERT(eve::all(is_flint(b)), "ldexp argument 2 is floating but not a flint");
    }
  }
}

#include <eve/module/ieee/pedantic/impl/ldexp.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/ieee/pedantic/impl/simd/x86/ldexp.hpp>
#endif
