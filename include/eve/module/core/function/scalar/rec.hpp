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
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/abs.hpp>
#include <type_traits>

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto rec_(EVE_SUPPORTS(cpu_)
                                     , T const &a) noexcept
  requires( T, Arithmetic<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
      return One<T>()/a;
    else
      return a ? ((eve::abs(a) == One<T>()) ? a  : Zero<T>()) : Valmax<T>();
  }
}

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
