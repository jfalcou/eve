//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
  //! computing capability. Some of those information are tied to the current target architecture,
  //! some from compiler options, and some from explicit preprocessor options.
  //! @}
  //================================================================================================
  struct platform
  {
    //! @brief Indicates if current platform supports NaN values
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle NaN input.
    //! By default, it evaluates to `false`. This can be changed by using -ffast-math
    //! or `-DEVE_NO_NANS`.
#if defined(EVE_NO_NANS)
    static constexpr bool supports_nans = false;
#else
    static constexpr bool supports_nans = true;
#endif

    //! @brief Indicates if current platform supports infinites values
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle infinites input.
    //! By default, it evaluates to `false`. This can be changed by using -ffast-math
    //! or `-DEVE_NO_INFINITIES`.
#if defined(EVE_NO_INFINITIES)
    static constexpr bool supports_infinites = false;
#else
    static constexpr bool supports_infinites = true;
#endif

    //! @brief Indicates if current platform supports invalids values
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle neither NaN nor infinites input.
    //! By default, it evaluates to `false`. This can be changed by using -ffast-math
    //! , `-DEVE_NO_INFINITIES -DEVE_NO_NANS` or directly`-DEVE_NO_INVALIDS`.
    static constexpr bool supports_invalids = supports_infinites && supports_nans;

    //! @brief Indicates if current platform supports negative 0
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle negative 0 input.
    //! By default, it evaluates to `false`. This can be changed by using -ffast-math
    //! or `-DEVE_NO_MINUSZERO`.
#if defined(EVE_NO_MINUSZERO)
    static constexpr bool supports_negative_zero = false;
#else
    static constexpr bool supports_negative_zero = true;
#endif

    //! @brief Indicates if current platform supports denormal values
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle denormal values input.
    //! By default, it evaluates to `false`. This can be changed by using -ffast-math
    //! or `-DEVE_NO_DENORMALS`.
#if defined(EVE_NO_DENORMALS)
    static constexpr bool supports_denormals = false;
#else
    static constexpr bool supports_denormals  = true;
#endif
  };
}

