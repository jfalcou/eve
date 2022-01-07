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
  //================================================================================================
  //! @addtogroup arch
  //! @{
  //! @struct platform
  //! @brief  Platform specific constexpr information
  //!
  //! Provides constexpr information about the status (supported or not) of various platform
  //! computing capability.
  //! @}
  //================================================================================================
  struct platform
  {
    //! @brief Evaluates to `true` if current platform supports NaN values
#if defined(EVE_NO_NANS)
    static constexpr bool supports_nans = false;
#else
    static constexpr bool supports_nans = true;
#endif

    //! @brief Evaluates to `true` if current platform supports infinites values
#if defined(EVE_NO_INFINITIES)
    static constexpr bool supports_infinites = false;
#else
    static constexpr bool supports_infinites = true;
#endif

    //! @brief Evaluates to `true` if current platform supports invalid values
    static constexpr bool supports_invalids = supports_infinites && supports_nans;

    //! @brief Evaluates to `true` if current platform supports negative 0
#if defined(EVE_NO_MINUSZERO)
    static constexpr bool supports_negative_zero = false;
#else
    static constexpr bool supports_negative_zero = true;
#endif

    //! @brief Evaluates to `true` if current platform supports denormal values
#if defined(EVE_NO_DENORMALS)
    static constexpr bool supports_denormals = false;
#else
    static constexpr bool supports_denormals  = true;
#endif
  };
}

