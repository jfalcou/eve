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
#include <type_traits>

namespace eve
{
  template<typename T> concept scalar_pointer = requires(T a)
  {
    { *a };
    requires scalar_value<std::remove_cvref_t<decltype(*a)>>;
  };
}
