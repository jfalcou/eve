//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_ALLBITS_HPP_INCLUDED
#define EVE_CONSTANT_ALLBITS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(allbits_, allbits_);

  template<typename T>
  EVE_FORCEINLINE auto Allbits(as_<T> const & = {})
  {
    using t_t           = detail::value_type_t<T>;
    using i_t           = detail::as_integer_t<t_t, unsigned>;
    constexpr auto mask = ~0ULL;

    if constexpr(std::is_integral_v<t_t>)
      return T(mask);
    else
      return T(bit_cast(i_t(mask), as_<t_t>() ));
  }

  EVE_MAKE_NAMED_CONSTANT(allbits_, Allbits);
}

#endif
