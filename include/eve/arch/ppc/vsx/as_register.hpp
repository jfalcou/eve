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
  template<typename T>
  struct logical;

  namespace ext
  {
    template<typename Size>
    struct as_register<double, Size, eve::ppc_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = __vector double;
    };

    template<typename Size>
    struct as_register<std::int64_t, Size, eve::ppc_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = __vector signed long;
    };

    template<typename Size>
    struct as_register<std::uint64_t, Size, eve::ppc_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = __vector unsigned long;
    };

    // logical cases
    template<typename Size>
    struct as_register<logical<double>, Size, eve::ppc_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = __vector __bool long;
    };

    template<typename Size>
    struct as_register<logical<std::int64_t>, Size, eve::ppc_, std::enable_if_t<(Size::value <= 2)>>
    {
      using type = __vector __bool long;
    };

    template<typename Size>
    struct as_register<logical<std::uint64_t>,
                       Size,
                       eve::ppc_,
                       std::enable_if_t<(Size::value <= 2)>>
    {
      using type = __vector __bool long;
    };
  }
}

#endif
