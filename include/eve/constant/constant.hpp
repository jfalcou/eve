//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_CONSTANT_HPP_INCLUDED
#define EVE_CONSTANT_CONSTANT_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T, auto BitsPattern>
  EVE_FORCEINLINE auto Constant(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;

    if constexpr(std::is_integral_v<t_t>)
    {
      return static_cast<T>(BitsPattern);
    }
    else
    {
      if constexpr(sizeof(t_t) != sizeof(BitsPattern))
      {
        static_assert ( sizeof(t_t) == sizeof(BitsPattern),
                        "[eve::constant] floating_point case - BitsPattern has not the correct size"
                      );
        return T{};
      }
      else
      {
        return static_cast<T>(bit_cast(BitsPattern,as_<t_t>{}));
      }
    }
  }
}

#endif
