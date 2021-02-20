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

#include <eve/arch/cpu/wide.hpp>
#include <eve/arch/cpu/logical_wide.hpp>
#include <eve/detail/std_api.hpp>
#include <eve/detail/meta.hpp>

//==================================================================================================
// Specific meta overloads
//==================================================================================================
namespace eve::detail
{
  template<typename T, typename N, typename ABI>
  struct as_floating_point<wide<T,N,ABI>>
  {
    using type = wide<as_floating_point_t<T>, N>;
  };

  template<typename T>
  struct as_floating_point<logical<T>>
  {
    using type = logical< as_floating_point_t<T> >;
  };
}
