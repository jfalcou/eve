//==================================================================================================
/**
  EVE - Expressive __vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_VMX_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_PPC_VMX_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/ppc/vmx/tags.hpp>
#include <eve/ext/as_register.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

namespace eve
{
  template<typename T> struct logical;

  namespace ext
  {
    template<int N> struct as_register<float, N, eve::ppc_, std::enable_if_t<(N<=4)>>
    {
      using type = __vector float;
    };

    template<int N> struct as_register<std::int32_t, N, eve::ppc_, std::enable_if_t<(N<=4)>>
    {
      using type = __vector signed int;
    };

    template<int N> struct as_register<std::int16_t, N, eve::ppc_, std::enable_if_t<(N<=8)>>
    {
      using type = __vector signed short;
    };

    template<int N> struct as_register<std::int8_t, N, eve::ppc_, std::enable_if_t<(N<=16)>>
    {
      using type = __vector signed  char;
    };

    template<int N> struct as_register<std::uint32_t, N, eve::ppc_, std::enable_if_t<(N<=4)>>
    {
      using type = __vector unsigned int;
    };

    template<int N> struct as_register<std::uint16_t, N, eve::ppc_, std::enable_if_t<(N<=8)>>
    {
      using type = __vector unsigned short;
    };

    template<int N> struct as_register<std::uint8_t, N, eve::ppc_, std::enable_if_t<(N<=16)>>
    {
      using type = __vector unsigned char;
    };

    // logical cases
    template<int N> struct as_register<logical<float>, N, eve::ppc_, std::enable_if_t<(N<=4)>>
    {
      using type = __vector __bool int;
    };

    template<int N> struct as_register<logical<std::int32_t>, N, eve::ppc_, std::enable_if_t<(N<=4)>>
    {
      using type = __vector __bool int;
    };

    template<int N> struct as_register<logical<std::int16_t>, N, eve::ppc_, std::enable_if_t<(N<=8)>>
    {
      using type = __vector __bool short;
    };

    template<int N> struct as_register<logical<std::int8_t>, N, eve::ppc_, std::enable_if_t<(N<=16)>>
    {
      using type = __vector __bool  char;
    };

    template<int N> struct as_register<logical<std::uint32_t>, N, eve::ppc_, std::enable_if_t<(N<=4)>>
    {
      using type = __vector __bool int;
    };

    template<int N> struct as_register<logical<std::uint16_t>, N, eve::ppc_, std::enable_if_t<(N<=8)>>
    {
      using type = __vector __bool short;
    };

    template<int N> struct as_register<logical<std::uint8_t>, N, eve::ppc_, std::enable_if_t<(N<=16)>>
    {
      using type = __vector __bool char;
    };
  }
}

#endif
