//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MANTISSAMASK_HPP_INCLUDED
#define EVE_CONSTANT_MANTISSAMASK_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/constant.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(mantissamask_, mantissamask_);

  template<typename T>
  EVE_FORCEINLINE auto Mantissamask(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>) return Constant<T, 0x807FFFFFU>();
    else if constexpr(std::is_same_v<t_t, double>) return Constant<T, 0x800FFFFFFFFFFFFFULL>();
    else return  ~T(0);
  }

  EVE_MAKE_NAMED_CONSTANT(mantissamask_, Mantissamask);
}

#endif
