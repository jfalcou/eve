//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if __has_include(<raberu/raberu.hpp>)
# include <raberu/raberu.hpp>
#else
# if defined(EVE_USE_EXTERNAL_DEPENDENCIES)
#   error "[EVE] External RABERU dependencies requested but none is available"
#   include <raberu/raberu.hpp>
# else
#   include <eve/deps/raberu/raberu.hpp>
# endif
#endif
