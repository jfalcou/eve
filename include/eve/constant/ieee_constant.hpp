//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_IEEE_CONSTANT_IEEE_CONSTANT_HPP_INCLUDED
#define EVE_IEEE_CONSTANT_IEEE_CONSTANT_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T, auto BitsPatternfloat, auto BitsPatterndouble>
  EVE_FORCEINLINE auto Ieee_constant(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;
    static_assert ( std::is_floating_point_v<t_t>
                  , "[eve::Iee_constant] -this function is not to be used with integralValue template parameter"
                  );
    
    using i_t = detail::as_integer_t<t_t, unsigned>;
    if constexpr(std::is_same_v<t_t, float>)
      return T(bitwise_cast<t_t>(i_t(BitsPatternfloat)));
    else
      return T(bitwise_cast<t_t>(i_t(BitsPatterndouble)));
  }
}

#endif
