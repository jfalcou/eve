//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/pattern.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(zero_, zero);

  // Acts as a pattern itself
  template<> struct is_pattern<tag::zero_> : std::true_type {};

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto zero_(EVE_SUPPORTS(cpu_), eve::as_<T> const &) noexcept
    {
      return T(0);
    }

    // Swizzle pattern interface
    template<simd_value Wide>
    EVE_FORCEINLINE auto zero_(EVE_SUPPORTS(cpu_), Wide const&) noexcept
    {
      return Wide{0};
    }

    template<simd_value Wide, shuffle_pattern Pattern>
    EVE_FORCEINLINE auto zero_(EVE_SUPPORTS(cpu_), Wide const&, Pattern) noexcept
    {
      return as_wide_t<Wide,fixed<Pattern::size(cardinal_v<Wide>)>>{0};
    }
  }
}
