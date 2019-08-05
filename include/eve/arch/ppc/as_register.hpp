//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_PPC_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/ppc/predef.hpp>
#include <eve/ext/as_register.hpp>
#include <type_traits>

namespace eve
{
  template<typename T> struct logical;
  struct ppc_;
}

#if EVE_HW_POWERPC >= EVE_VMX_VERSION
namespace eve::ext
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
#endif

#if EVE_HW_POWERPC >= EVE_VSX_VERSION
namespace eve::ext
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
#endif

#endif
