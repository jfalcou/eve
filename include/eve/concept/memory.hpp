//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/vectorizable.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <type_traits>

namespace eve
{
  namespace detail
  {
    template<typename T> struct is_scalar_pointer : std::is_pointer<T> {};

    template<typename T, std::size_t A>
    struct is_scalar_pointer<aligned_ptr<T,A>> : std::true_type {};
  }

  template<typename T> concept scalar_pointer = detail::is_scalar_pointer<T>::value;
}
