//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/spy.hpp>
#include <type_traits>

#ifndef EVE_NO_STRICT_ALIASING
#  if defined(EVEV_COMP_IS_MSVC)
#    define EVE_NO_STRICT_ALIASING
#  endif
#  if defined(SPY_COMPILER_IS_GNUC)
#    define EVE_MAY_ALIAS __attribute__((may_alias))
#  endif
#endif

#ifndef EVE_MAY_ALIAS
#  define EVE_MAY_ALIAS
#endif

namespace eve::detail
{
  template<typename T> struct alias
  {
    typedef T EVE_MAY_ALIAS type;
  };

  template<typename T> requires( std::is_class_v<T> )
  struct alias<T>
  {
    using type = T;
  };

  template<typename T>
  using alias_t = typename alias<T>::type;
}

