//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_REC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_REC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/tags.hpp>
#include <type_traits>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4723) // potential divide by 0
#endif

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto rec_(EVE_SUPPORTS(cpu_),
                                      T const &a) noexcept requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>) { return T{1} / a; }
    else if(std::is_integral_v<T>)
    {
      // Generates a branch-less rec by triggering the use of conditional moves
      if(std::is_unsigned_v<T>)
      {
        auto b = a > 1 ? 0 : 1;
        return (a ? 1 : Valmax(as(a))) * b;
      }
      else
      {
        auto b1 = a > 1 ? 0 : 1;
        auto b2 = a < -1 ? 0 : 1;
        b2 *= b1;

        return (a ? a : Valmax(as(a))) * b2;
      }
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  rec_(EVE_SUPPORTS(cpu_), raw_type const &, T const &a) noexcept requires(T, Vectorizable<T>)
  {
    return eve::rec(a);
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto
  rec_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a) noexcept requires(T, Vectorizable<T>)
  {
    return eve::rec(a);
  }
}

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#endif
