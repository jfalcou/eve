//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_CPU_AS_REGISTER_HPP_INCLUDED

#include <array>
#include <eve/ext/as_register.hpp>

namespace eve { namespace ext
{
  template<typename Type, int Cardinal>
  struct as_register<Type, Cardinal, eve::emulated_>
  {
    using type = std::array<Type,Cardinal>;
  };
} }

#endif
