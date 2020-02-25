//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_PIO_4_HPP_INCLUDED
#define EVE_CONSTANT_PIO_4_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(pio_4_, pio_4_);

  template<typename T>
  EVE_FORCEINLINE auto Pio_4(as_<T> const & = {})
  {
    using t_t =  detail::value_type_t<T>;
    if constexpr(std::is_same_v<t_t, float>) return Constant<T,   0X3F490FDB>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T,  0X3FE921FB54442D18LL>();
    if constexpr(std::is_integral_v<t_t>) return T(1);
  }
  
  EVE_MAKE_NAMED_CONSTANT(pio_4_, Pio_4);
}

#endif

