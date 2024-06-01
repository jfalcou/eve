//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#define KUMI_NO_STD_ADAPTORS
#if __has_include(<kumi/tuple.hpp>)
# include <kumi/tuple.hpp>
#else
# if defined(EVE_USE_EXTERNAL_DEPENDENCIES)
#   error "[EVE] External KUMI dependencies requested but none is available"
#   include <kumi/tuple.hpp>
# else
#   include <eve/deps/kumi/tuple.hpp>
# endif
#endif
