//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MINLOG10_HPP_INCLUDED
#define EVE_CONSTANT_MINLOG10_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
/*
    if T is double
    r = -308.2547155599167;
    else if T is float
    r = -37.89999771118164;
*/
namespace eve
{
  EVE_MAKE_CALLABLE(minlog10_, minlog10_);

  template<typename T>
  constexpr EVE_FORCEINLINE auto Minlog10(as_<T> const & = {}) noexcept
  requires(T, detail::behave_as<detail::floating_point, T>)
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0xc2179999U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0xc0734413509f79feULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(minlog10_, Minlog10);
}

#endif
