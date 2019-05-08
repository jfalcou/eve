//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_CPU_AS_REGISTER_HPP_INCLUDED

#include <eve/ext/as_register.hpp>
#include <eve/forward.hpp>

namespace eve::ext
{
  template<typename Type, typename Cardinal>
  struct as_register<Type, Cardinal, eve::emulated_>
  {
    using type = std::array<Type, Cardinal::value>;
  };

  template<typename Type, typename Cardinal>
  struct as_register<Type, Cardinal, eve::aggregated_>
  {
    using substorage_type = eve::wide<Type, typename Cardinal::split_type>;
    struct type
    {
      using value_type = substorage_type;
      substorage_type lo, hi;
    };
  };
}

#endif
