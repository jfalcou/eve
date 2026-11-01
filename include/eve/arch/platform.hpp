//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

// Captures math related options and translate to proper setup
#if defined(__FAST_MATH__) && !defined(EVE_FAST_MATH)
#  define EVE_FAST_MATH
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_NANS)
#  define EVE_NO_NANS
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_MINUSZERO)
#  define EVE_NO_MINUSZERO
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_INFINITIES)
#  define EVE_NO_INFINITIES
#endif

#if defined(EVE_FAST_MATH) && !defined(EVE_NO_DENORMALS)
#  define EVE_NO_DENORMALS
#endif

#if defined(EVE_NO_NANS) && defined(EVE_NO_INFINITIES) && !defined(EVE_NO_INVALIDS)
#  define EVE_NO_INVALIDS
#elif defined(EVE_NO_INVALIDS)
#  define EVE_NO_NANS
#  define EVE_NO_INFINITIES
#endif

namespace eve
{
  //================================================================================================
  //! @addtogroup eve_arch
  //! @{
  //!   @namespace platform
  //!   @brief  Platform specific constexpr information
  //!
  //!   Provides constexpr information about the status (supported or not) of various platform
  //!   computing capability. Some of those information are tied to the current target architecture,
  //!   some from compiler options, and some from explicit preprocessor options.
  //! @}
  //================================================================================================
  namespace platform
  {
    //! @brief Indicates if current platform supports hardware fuse multiply add 
    //! If this value evaluates to `true`, implementation of functions will use FMAs the same
    //! way on vector or scalar inputs in order to avoid rounding differently.
#if defined(__FMA__) || defined(__ARM_FEATURE_FMA) || defined(__VSX__) || defined(__riscv_f)
  inline constexpr bool supports_hardware_fma = true;
#else
  inline constexpr bool supports_hardware_fma = false;
#endif

    //! @brief Indicates if current platform supports simd operations
    //! If this value evaluates to `false`, implementation of functions will emulate simd operations using arrays.    
    //! By default, it evaluates to `true`. This can be changed by using `-DEVE_NO_SIMD`.
# if defined(EVE_NO_SIMD)
  inline constexpr bool supports_simd = false;
# else
  inline constexpr bool supports_simd = true;
#endif

    //! @brief Indicates if current platform supports NaN values
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle NaN input.
    //! By default, it evaluates to `true`. This can be changed by using -ffast-math
    //! or `-DEVE_NO_NANS`.
#if defined(EVE_NO_NANS)
    inline constexpr bool supports_nans = false;
#else
    inline constexpr bool supports_nans = true;
#endif

    //! @brief Indicates if current platform supports infinites values
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle infinites input.
    //! By default, it evaluates to `true`. This can be changed by using -ffast-math
    //! or `-DEVE_NO_INFINITIES`.
#if defined(EVE_NO_INFINITIES)
    inline constexpr bool supports_infinites = false;
#else
    inline constexpr bool supports_infinites = true;
#endif

    //! @brief Indicates if current platform supports invalids values
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle neither NaN nor infinites input.
    //! By default, it evaluates to `true`. This can be changed by using -ffast-math
    //! , `-DEVE_NO_INFINITIES -DEVE_NO_NANS` or directly`-DEVE_NO_INVALIDS`.
    inline constexpr bool supports_invalids = supports_infinites && supports_nans;

    //! @brief Indicates if current platform supports negative 0
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle negative 0 input.
    //! By default, it evaluates to `true`. This can be changed by using -ffast-math
    //! or `-DEVE_NO_MINUSZERO`.
#if defined(EVE_NO_MINUSZERO)
    inline constexpr bool supports_negative_zero = false;
#else
    inline constexpr bool supports_negative_zero = true;
#endif

    //! @brief Indicates if current platform supports denormal values
    //! If this value evaluates to `true`, implementation of functions will not take any special
    //! provision to handle denormal values input.
    //! By default, it evaluates to `true`. This can be changed by using -ffast-math
    //! or `-DEVE_NO_DENORMALS`.
#if defined(EVE_NO_DENORMALS)
    inline constexpr bool supports_denormals = false;
#else
    inline constexpr bool supports_denormals  = true;
#endif
  };
}
