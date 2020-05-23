//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_SMALLESTPOSVAL_HPP_INCLUDED
#define EVE_CONSTANT_SMALLESTPOSVAL_HPP_INCLUDED

#include <eve/constant/constant.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta/traits.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(smallestposval_, smallestposval_);

  template<typename T>
  EVE_FORCEINLINE auto Smallestposval(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>)
      {
        return Constant<T, 0X00800000U>();
      }
    else if constexpr(std::is_same_v<t_t, double>)
      {
        return Constant<T, 0X0010000000000000ULL>();
      }
    else if constexpr(std::is_integral_v<t_t>)
      {
        return T(1);
      }
  }

  EVE_MAKE_NAMED_CONSTANT(smallestposval_, Smallestposval);
}

#endif
