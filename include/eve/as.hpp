//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_AS_HPP_INCLUDED
#define EVE_AS_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <type_traits>

namespace eve
{
  template<typename T> struct as_ { using type = T; };

  template<typename T>
  EVE_FORCEINLINE constexpr as_<std::decay_t<T>> as(T&&) noexcept
  {
    return {};
  }
}

#endif
