//==================================================================================================
/**
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_CPU_AS_REGISTER_HPP_INCLUDED

#include <array>
#include <eve/arch/as_register.hpp>

namespace eve { namespace ext
{
  template<typename Type, int Cardinal>
  struct as_register<Type, Cardinal, eve::cpu_>
  {
    using type = std::array<Type,Cardinal>;
  };
} }

#endif
