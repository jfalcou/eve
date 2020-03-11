//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_NAN_HPP_INCLUDED
#define EVE_CONSTANT_NAN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(nan_, nan_);

  template<typename T>
  EVE_FORCEINLINE auto Nan(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_integral_v<t_t>)
      return Zero<T>();
    else
      return Allbits<T>();
  }

  EVE_MAKE_NAMED_CONSTANT(nan_, Nan);
}

#endif
