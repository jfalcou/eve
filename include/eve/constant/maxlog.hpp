//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MAXLOG_HPP_INCLUDED
#define EVE_CONSTANT_MAXLOG_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
/*
  if T is double
  r = 709.78271289338400;
  else if T is float
  r =  88.3762626647949
*/
namespace eve
{
  EVE_MAKE_CALLABLE(maxlog_, maxlog_);

  template<typename T>
  constexpr EVE_FORCEINLINE auto Maxlog(as_<T> const & = {}) noexcept
  requires(T, detail::behave_as<detail::floating_point, T>)
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x42b0c0a5U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x40862e42fefa39efULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(maxlog_, Maxlog);
}

#endif
