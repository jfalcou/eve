//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_SQRT_2_HPP_INCLUDED
#define EVE_CONSTANT_SQRT_2_HPP_INCLUDED

#include <eve/detail/overload.hpp> 
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(sqrt_2_, sqrt_2_);

  template<typename T>
  EVE_FORCEINLINE auto Sqrt_2(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x3FB504F3>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x3ff6A09E667F3BCCULL>();
    if constexpr(std::is_integral_v<t_t>) return T(1);

  }

  EVE_MAKE_NAMED_CONSTANT(sqrt_2_, Sqrt_2);
}

#endif
