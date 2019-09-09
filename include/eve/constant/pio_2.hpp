//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_PIO_2_HPP_INCLUDED
#define EVE_CONSTANT_PIO_2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(pio_2_, pio_2_);

  template<typename T>
  EVE_FORCEINLINE auto Pio_2(as_<T> const & = {})
  {
    using t_t =  detail::value_type_t<T>;
    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x3fc90fdbUL>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x3ff921fb54442d18ULL>();
    if constexpr(std::is_integral_v<t_t>) return T(2);
  }

  EVE_MAKE_NAMED_CONSTANT(pio_2_, Pio_2);
}

#endif
