//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MAXLOG2_HPP_INCLUDED
#define EVE_CONSTANT_MAXLOG2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
/*
   if T is double
    r = 1023.0;
    else if T is float
    r = 127.0;
*/
namespace eve
{
  EVE_MAKE_CALLABLE(maxlog2_, maxlog2_);

  template<typename T>
  constexpr EVE_FORCEINLINE auto Maxlog2(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x42fe0000U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x408ff80000000000ULL>();
    if constexpr(std::is_integral_v<t_t>)
    {
      if constexpr(std::is_signed_v<t_t>) return T(sizeof(t_t)*8-2);
      else return T(sizeof(t_t)*8-1);            
    }
  }

    EVE_MAKE_NAMED_CONSTANT(maxlog2_, Maxlog2);
}

#endif
