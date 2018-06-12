//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_OS_HPP_INCLUDED
#define EVE_DETAIL_OS_HPP_INCLUDED

// Detect if we are using Linux
#if !defined(EVE_OS_DETECTED) && (defined(linux) || defined(__linux))
#define EVE_OS_IS_LINUX
#define EVE_OS_DETECTED
#endif

// Detect if we are using MacOS
#if !defined(EVE_OS_DETECTED)                       \
  &&  (   defined(macintosh) || defined(Macintosh)  \
      || (defined(__APPLE__) && defined(__MACH__))  \
      )
#define EVE_OS_IS_MACOS
#define EVE_OS_DETECTED
#endif

// Detect if we are using Unix
#if !defined(EVE_OS_DETECTED)                             \
  &&  (  defined(unix)          || defined(__unix)        \
      || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE) \
      )
#define EVE_OS_IS_UNIX
#define EVE_OS_DETECTED
#endif

// Detect if we are using Windows
#if !defined(EVE_OS_DETECTED)                                           \
  &&  ( defined(_WIN32)       || defined(__WIN32__) || defined(_WIN64)  \
      || defined(__TOS_WIN__) || defined(__WINDOWS__)                   \
      )
#define EVE_OS_IS_WINDOWS
#define EVE_OS_DETECTED
#endif

#endif
