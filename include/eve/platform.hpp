//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  struct platform
  {
#if defined(EVE_NO_NANS)
    static constexpr bool supports_nans = false;
#else
    static constexpr bool supports_nans = true;
#endif

#if defined(EVE_NO_INFINITIES)
    static constexpr bool supports_infinites = false;
#else
    static constexpr bool supports_infinites = true;
#endif

    static constexpr bool supports_invalids = supports_infinites && supports_nans;

#if defined(EVE_NO_MINUSZERO)
    static constexpr bool supports_negative_zero = false;
#else
    static constexpr bool supports_negative_zero = true;
#endif

#if defined(EVE_NO_DENORMALS)
    static constexpr bool supports_denormals = false;
#else
    static constexpr bool supports_denormals  = true;
#endif
  };
}

