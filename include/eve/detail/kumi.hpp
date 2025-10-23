//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if __has_include(<kumi/kumi.hpp>)
# include <kumi/kumi.hpp>
#else
# if defined(EVE_USE_EXTERNAL_DEPENDENCIES)
#   error "[EVE] External KUMI dependencies requested but none are available"
#   include <kumi/kumi.hpp>
# else
#   include <eve/deps/kumi/tuple.hpp>
# endif
#endif
