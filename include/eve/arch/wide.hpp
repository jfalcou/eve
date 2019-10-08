//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_WIDE_HPP_INCLUDED
#define EVE_ARCH_WIDE_HPP_INCLUDED

#include <eve/arch/cpu/wide.hpp>
#include <eve/arch/cpu/logical_wide.hpp>
#include <eve/detail/std_api.hpp>
#include <eve/detail/meta.hpp>

//==================================================================================================
// Specific meta overloads
//==================================================================================================
namespace eve::detail
{
  template<typename T, typename N, typename ABI, typename Sign>
  struct as_integer<wide<T,N,ABI>, Sign>
  {
    using type = wide<as_integer_t<T,Sign>, N>;
  };

  template<typename T, typename Sign>
  struct as_integer<logical<T>, Sign>
  {
    using type = logical< as_integer_t<T,Sign> >;
  };

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

  template<typename T> struct sign_of<logical<T>> : sign_of<T> {};
}

#endif
