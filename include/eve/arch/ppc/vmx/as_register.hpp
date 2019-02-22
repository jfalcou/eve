//==================================================================================================
/**
  EVE - Expressive __vector Engine
  Copyright 2019 Joel FALCOU

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
  template<typename T>
  struct logical;

  namespace ext
  {
    template<typename Size>
    struct as_register<float, Size, eve::ppc_, std::enable_if_t<(Size::value <= 4)>>
    {
      using type = __vector float;
    };

    template<typename Size>
    struct as_register<std::int32_t, Size, eve::ppc_, std::enable_if_t<(Size::value <= 4)>>
    {
      using type = __vector signed int;
    };

    template<typename Size>
    struct as_register<std::int16_t, Size, eve::ppc_, std::enable_if_t<(Size::value <= 8)>>
    {
      using type = __vector signed short;
    };

    template<typename Size>
    struct as_register<std::int8_t, Size, eve::ppc_, std::enable_if_t<(Size::value <= 16)>>
    {
      using type = __vector signed char;
    };

    template<typename Size>
    struct as_register<std::uint32_t, Size, eve::ppc_, std::enable_if_t<(Size::value <= 4)>>
    {
      using type = __vector unsigned int;
    };

    template<typename Size>
    struct as_register<std::uint16_t, Size, eve::ppc_, std::enable_if_t<(Size::value <= 8)>>
    {
      using type = __vector unsigned short;
    };

    template<typename Size>
    struct as_register<std::uint8_t, Size, eve::ppc_, std::enable_if_t<(Size::value <= 16)>>
    {
      using type = __vector unsigned char;
    };

    // logical cases
    template<typename Size>
    struct as_register<logical<float>, Size, eve::ppc_, std::enable_if_t<(Size::value <= 4)>>
    {
      using type = __vector __bool int;
    };

    template<typename Size>
    struct as_register<logical<std::int32_t>, Size, eve::ppc_, std::enable_if_t<(Size::value <= 4)>>
    {
      using type = __vector __bool int;
    };

    template<typename Size>
    struct as_register<logical<std::int16_t>, Size, eve::ppc_, std::enable_if_t<(Size::value <= 8)>>
    {
      using type = __vector __bool short;
    };

    template<typename Size>
    struct as_register<logical<std::int8_t>, Size, eve::ppc_, std::enable_if_t<(Size::value <= 16)>>
    {
      using type = __vector __bool char;
    };

    template<typename Size>
    struct as_register<logical<std::uint32_t>,
                       Size,
                       eve::ppc_,
                       std::enable_if_t<(Size::value <= 4)>>
    {
      using type = __vector __bool int;
    };

    template<typename Size>
    struct as_register<logical<std::uint16_t>,
                       Size,
                       eve::ppc_,
                       std::enable_if_t<(Size::value <= 8)>>
    {
      using type = __vector __bool short;
    };

    template<typename Size>
    struct as_register<logical<std::uint8_t>,
                       Size,
                       eve::ppc_,
                       std::enable_if_t<(Size::value <= 16)>>
    {
      using type = __vector __bool char;
    };
  }
}

#endif
