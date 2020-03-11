//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MZERO_HPP_INCLUDED
#define EVE_CONSTANT_MZERO_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(mzero_, mzero_);

  template<typename T>
  EVE_FORCEINLINE auto Mzero(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_same_v<t_t, float>)
      return T(-0.0f);
    else if constexpr(std::is_same_v<t_t, double>)
      return T(-0.0);
    else
      return T(0);
  }

  EVE_MAKE_NAMED_CONSTANT(mzero_, Mzero);
}

#endif
