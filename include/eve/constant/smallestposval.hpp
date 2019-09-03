//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_SMALLESTPOSVAL_HPP_INCLUDED
#define EVE_CONSTANT_SMALLESTPOSVAL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(smallestposval_, smallestposval_);

  template<typename T>
  EVE_FORCEINLINE auto Smallestposval(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0X00800000U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X0010000000000000ULL>();
    if constexpr(std::is_integral_v<t_t>) return T(1);
  }

  EVE_MAKE_NAMED_CONSTANT(smallestposval_, Smallestposval);
}

#endif
