//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_ALIAS_HPP_INCLUDED
#define EVE_DETAIL_ALIAS_HPP_INCLUDED

#include <eve/detail/compiler.hpp>
#include <type_traits>

#ifndef EVE_NO_STRICT_ALIASING
#if defined(EVEV_COMP_IS_MSVC)
#define EVE_NO_STRICT_ALIASING
#endif
#if defined(EVE_COMP_IS_GNUC)
#define EVE_MAY_ALIAS __attribute__((may_alias))
#endif
#endif

#ifndef EVE_MAY_ALIAS
#define EVE_MAY_ALIAS
#endif

namespace eve::detail
{
  template<typename T, typename EnableIf = void>
  struct alias
  {
    typedef T EVE_MAY_ALIAS type;
  };

  template<typename T> struct alias<T,std::enable_if_t<std::is_class_v<T>>>
  {
    using type = T;
  };

  template<typename T> using alias_t =  typename alias<T>::type;
}

#endif
