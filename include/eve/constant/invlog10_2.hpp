//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_INVLOG10_2_HPP_INCLUDED
#define EVE_CONSTANT_INVLOG10_2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(invlog10_2_, invlog10_2_);

  template<typename T>
  constexpr EVE_FORCEINLINE auto Invlog10_2(as_<T> const & = {}) noexcept
  Requires(T, detail::behave_as<detail::floating_point, T>)
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T,  0x40549a78U>();
    if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x400a934f0979a371ULL>();
  }

  EVE_MAKE_NAMED_CONSTANT(invlog10_2_, Invlog10_2);
}

#endif
