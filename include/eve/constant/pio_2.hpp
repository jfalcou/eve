//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_PIO_2_HPP_INCLUDED
#define EVE_CONSTANT_PIO_2_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(pio_2_, pio_2_);

  template<floating_value T>
  EVE_FORCEINLINE auto Pio_2(as_<T> const & = {}) noexcept
  {
    using t_t =  detail::value_type_t<T>;
    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x3fc90fdbU>();
    else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x3ff921fb54442d18ULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(pio_2_, Pio_2);
}

#endif
