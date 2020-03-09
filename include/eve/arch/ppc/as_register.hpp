//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_AS_REGISTER_HPP_INCLUDED
#define EVE_ARCH_PPC_AS_REGISTER_HPP_INCLUDED

#include <eve/arch/ppc/predef.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
  struct ppc_;
}

#if defined(EVE_HW_PPC)
namespace eve
{
  template<typename T, typename Size> struct as_register<T, Size, eve::ppc_>
  {
    template<typename U> static constexpr bool is_logical(U const&)           { return false; }
    template<typename U> static constexpr bool is_logical(logical<U> const&)  { return true; }

    static constexpr bool size_check(std::size_t t, std::size_t s)
    {
      return (sizeof(T) == t) && (Size::value <= s);
    }

    static constexpr auto find()
    {
      if constexpr( std::is_same_v<T,float> && Size::value <= 4)
      {
        if constexpr(is_logical(T{})) return __vector bool int{};
        else                          return __vector float{};
      }
      else if constexpr( std::is_same_v<T,double> && Size::value <= 2 )
      {
        if constexpr(spy::simd_instruction_set == spy::vsx_)
        {
          if constexpr(is_logical(T{})) return __vector bool long{};
          else                          return __vector double{};
        }
        else
        {
          return emulated_{};
        }
      }
      else if constexpr( std::is_integral_v<T> )
      {
        constexpr bool signed_v = std::is_signed_v<T>;

        if constexpr( signed_v && size_check(1,8) && is_logical(T{}) ) return __vector bool char{};
        if constexpr( signed_v && size_check(1,8) && !is_logical(T{})) return __vector signed char{};
        if constexpr( signed_v && size_check(2,4) && is_logical(T{}) ) return __vector bool short{};
        if constexpr( signed_v && size_check(2,4) && !is_logical(T{})) return __vector signed short{};
        if constexpr( signed_v && size_check(4,2) && is_logical(T{}) ) return __vector bool int{};
        if constexpr( signed_v && size_check(4,2) && !is_logical(T{})) return __vector signed int{};
        if constexpr(!signed_v && size_check(1,8) && is_logical(T{}) ) return __vector bool char{};
        if constexpr(!signed_v && size_check(1,8) && !is_logical(T{})) return __vector unsigned char{};
        if constexpr(!signed_v && size_check(2,4) && is_logical(T{}) ) return __vector bool short{};
        if constexpr(!signed_v && size_check(2,4) && !is_logical(T{})) return __vector unsigned short{};
        if constexpr(!signed_v && size_check(4,2) && is_logical(T{}) ) return __vector bool int{};
        if constexpr(!signed_v && size_check(4,2) && !is_logical(T{})) return __vector unsigned int{};

        if constexpr(spy::simd_instruction_set == spy::vsx_)
        {
          if constexpr( signed_v && size_check(8,1) && is_logical(T{}) ) return __vector bool long{};
          if constexpr( signed_v && size_check(8,1) && !is_logical(T{})) return __vector signed long{};
          if constexpr(!signed_v && size_check(8,1) && is_logical(T{}) ) return __vector bool long{};
          if constexpr(!signed_v && size_check(8,1) && !is_logical(T{})) return __vector unsigned long{};
        }
        else
        {
          if constexpr(  signed_v && size_check(8,1) ) return emulated_{};
          if constexpr( !signed_v && size_check(8,1) ) return emulated_{};
        }
      }
    }

    using type = decltype(find());
  };
}
#endif

#endif
