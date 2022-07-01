//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/ppc/predef.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct logical;
}

#if defined(EVE_HW_POWERPC)
namespace eve
{
  namespace detail
  {
    template<typename T> using wrap = T;
  }

  template<typename T, typename Size> struct as_register<T, Size, eve::ppc_>
  {
    static constexpr bool size_check(std::size_t t, std::size_t s)
    {
      return (sizeof(T) == t) && (Size::value <= s);
    }

    static constexpr auto find()
    {
      using detail::wrap;

      if constexpr( std::is_same_v<T,float> && Size::value <= 4) { return wrap<__vector float>{}; }
      else if constexpr( std::is_same_v<T,double> && Size::value <= 2 )
      {
        if constexpr(spy::simd_instruction_set >= spy::vsx_)  { return wrap<__vector double>{}; }
        else                                                  { return emulated_{};         }
      }
      else if constexpr( std::is_integral_v<T> )
      {
        constexpr bool signed_v = std::is_signed_v<T>;

        if constexpr( signed_v && size_check(1,16)) return wrap<__vector signed char>{};
        if constexpr( signed_v && size_check(2,8 )) return wrap<__vector signed short>{};
        if constexpr( signed_v && size_check(4,4 )) return wrap<__vector signed int>{};
        if constexpr(!signed_v && size_check(1,16)) return wrap<__vector unsigned char>{};
        if constexpr(!signed_v && size_check(2,8 )) return wrap<__vector unsigned short>{};
        if constexpr(!signed_v && size_check(4,4 )) return wrap<__vector unsigned int>{};

        if constexpr(spy::simd_instruction_set >= spy::vsx_)
        {
          if constexpr( signed_v && size_check(8,2)) return wrap<__vector signed long>{};
          if constexpr(!signed_v && size_check(8,2)) return wrap<__vector unsigned long>{};
        }
        else
        {
          if constexpr( size_check(8,1) ) return emulated_{};
        }
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve ppc] - Type is not usable in a SIMD register");
  };

  template<typename T, typename Size> struct as_logical_register<T, Size, eve::ppc_>
  {
    static constexpr bool size_check(std::size_t t, std::size_t s)
    {
      return (sizeof(T) == t) && (Size::value <= s);
    }

    static constexpr auto find()
    {
      using detail::wrap;

      if constexpr( std::is_same_v<T,float> && Size::value <= 4) { return wrap<__vector __bool int>{}; }
      else if constexpr( std::is_same_v<T,double> && Size::value <= 2 )
      {
        if constexpr(spy::simd_instruction_set >= spy::vsx_)  { return wrap<__vector __bool long>{}; }
        else                                                  { return emulated_{}; }
      }
      else if constexpr( std::is_integral_v<T> )
      {
        constexpr bool signed_v = std::is_signed_v<T>;

        if constexpr( signed_v && size_check(1,16) ) return wrap<__vector __bool char>{};
        if constexpr( signed_v && size_check(2,8 ) ) return wrap<__vector __bool short>{};
        if constexpr( signed_v && size_check(4,4 ) ) return wrap<__vector __bool int>{};
        if constexpr(!signed_v && size_check(1,16) ) return wrap<__vector __bool char>{};
        if constexpr(!signed_v && size_check(2,8 ) ) return wrap<__vector __bool short>{};
        if constexpr(!signed_v && size_check(4,4 ) ) return wrap<__vector __bool int>{};

        if constexpr(spy::simd_instruction_set >= spy::vsx_)
        {
          if constexpr( signed_v && size_check(8,2) ) return wrap<__vector __bool long>{};
          if constexpr(!signed_v && size_check(8,2) ) return wrap<__vector __bool long>{};
        }
        else
        {
          if constexpr(size_check(8,2) ) return emulated_{};
        }
      }
    }

    using type = decltype(find());
    static_assert( !std::is_void_v<type>, "[eve ppc] - Type is not usable in a SIMD register");
  };
}
#endif
