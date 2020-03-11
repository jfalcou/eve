//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_ONEOTWOEPS_HPP_INCLUDED
#define EVE_CONSTANT_ONEOTWOEPS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(oneotwoeps_, oneotwoeps_);

  template<typename T>
  constexpr EVE_FORCEINLINE auto Oneotwoeps(as_<T> const & = {}) noexcept
  requires(T, detail::behave_as<detail::floating_point, T>)
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0X4A800000U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0X4320000000000000ULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(oneotwoeps_, Oneotwoeps);
}

#endif
