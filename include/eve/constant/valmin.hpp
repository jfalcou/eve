//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_VALMIN_HPP_INCLUDED
#define EVE_CONSTANT_VALMIN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(valmin_, valmin_);

  template<typename T>
  EVE_FORCEINLINE auto Valmin(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;
    return T(std::numeric_limits<t_t>::lowest());
  }

  EVE_MAKE_NAMED_CONSTANT(valmin_, Valmin);
}

#endif
