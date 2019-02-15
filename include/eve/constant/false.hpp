//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_FALSE_HPP_INCLUDED
#define EVE_CONSTANT_FALSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as_logical.hpp>
#include <eve/is_logical.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(false_, false_);

  template<typename T>
  EVE_FORCEINLINE std::enable_if_t<is_logical_v<T>, as_logical_t<T>> False(as_<T> const & = {})
  {
    return as_logical_t<T>(false);
  }

  template<typename T>
  EVE_FORCEINLINE std::enable_if_t<!is_logical_v<T>, as_logical_t<T>>
                  False(as_<T> const & = {}) = delete;

  EVE_MAKE_NAMED_CONSTANT(false_, False);
}

#endif
