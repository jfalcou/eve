//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_INVLOG_2_HPP_INCLUDED
#define EVE_CONSTANT_INVLOG_2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(invlog_2_, invlog_2_);

  template<typename T>
  constexpr EVE_FORCEINLINE auto Invlog_2(as_<T> const & = {}) noexcept
  requires(T, detail::behave_as<detail::floating_point, T>)
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0X3FB8AA3BU>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X3FF71547652B82FEULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(invlog_2_, Invlog_2);
}

#endif
