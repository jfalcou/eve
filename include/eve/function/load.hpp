//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/conditional.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(load_, load);

  template<> struct supports_optimized_conversion<tag::load_> : std::true_type {};
}

#include <eve/module/real/core/function/regular/generic/load.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/load.hpp>
#endif
