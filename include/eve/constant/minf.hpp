//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Jean-Thierry lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_MINF_HPP_INCLUDED
#define EVE_CONSTANT_MINF_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  EVE_MAKE_CALLABLE(minf_, minf_);

  template<typename T>
  EVE_FORCEINLINE auto Minf(as_<T> const & = {}) noexcept
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_integral_v<t_t>)
      return T(std::numeric_limits<t_t>::min());
    else
      return T(-std::numeric_limits<t_t>::infinity());
  }

  EVE_MAKE_NAMED_CONSTANT(minf_, Minf);
}

#endif
