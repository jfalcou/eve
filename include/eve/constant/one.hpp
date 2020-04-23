//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_ONE_HPP_INCLUDED
#define EVE_CONSTANT_ONE_HPP_INCLUDED

#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(one_, one_);

  template<typename T>
  EVE_FORCEINLINE auto One(as_<T> const & = {}) noexcept
  {
    return T(1);
  }

  EVE_MAKE_NAMED_CONSTANT(one_, One);
}

#endif
