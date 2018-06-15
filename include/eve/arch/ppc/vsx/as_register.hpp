//==================================================================================================
/**
  EVE - Expressive __vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_VSX_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_PPC_VSX_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/ppc/vsx/tags.hpp>
#include <eve/ext/as_register.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve
{
  template<typename T> struct logical;

  namespace ext
  {
    template<int N> struct as_register<double, N, eve::ppc_, std::enable_if_t<(N<=2)>>
    {
      using type = __vector double;
    };

    template<int N> struct as_register<std::int64_t, N, eve::ppc_, std::enable_if_t<(N<=2)>>
    {
      using type = __vector signed long;
    };

    template<int N> struct as_register<std::uint64_t, N, eve::ppc_, std::enable_if_t<(N<=2)>>
    {
      using type = __vector unsigned long;
    };

    // logical cases
    template<int N> struct as_register<logical<double>, N, eve::ppc_, std::enable_if_t<(N<=2)>>
    {
      using type = __vector __bool long;
    };

    template<int N> struct as_register<logical<std::int64_t>, N, eve::ppc_, std::enable_if_t<(N<=2)>>
    {
      using type = __vector __bool long;
    };

    template<int N> struct as_register<logical<std::uint64_t>, N, eve::ppc_, std::enable_if_t<(N<=2)>>
    {
      using type = __vector __bool long;
    };
  }
}

#endif
