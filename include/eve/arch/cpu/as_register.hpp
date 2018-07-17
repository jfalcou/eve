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
#include <eve/forward.hpp>

namespace eve { namespace ext
{
  template<typename Type, typename Cardinal>
  struct as_register<Type, Cardinal, eve::emulated_>
  {
    using type = std::array<Type,Cardinal::value>;
  };

  template<typename Type, typename Cardinal>
  struct as_register<Type, Cardinal, eve::aggregated_>
  {
    using substorage_type = eve::pack<Type,typename Cardinal::split_type>;
    using type = std::array<substorage_type,2>;
  };
} }

#endif
