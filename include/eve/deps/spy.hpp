//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#if __has_include(<spy/spy.hpp>)
# include <spy/spy.hpp>
#else
# if defined(EVE_USE_EXTERNAL_DEPENDENCIES)
#   error "[EVE] External SPY dependencies requested but none is available"
#   include <spy/spy.hpp>
# else
#   include <eve/deps/spy/spy.hpp>
# endif
#endif
