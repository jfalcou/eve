//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_IEEE_CONSTANT_IEEE_CONSTANT_HPP_INCLUDED
#define EVE_IEEE_CONSTANT_IEEE_CONSTANT_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  template<typename T, auto BitsPatternfloat, auto BitsPatterndouble>
  EVE_FORCEINLINE auto Ieee_constant(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;
    if constexpr(!std::is_floating_point_v<t_t>)
    {
      static_assert ( std::is_floating_point_v<t_t>
                    , "[eve::Iee_constant] -this function is not to be used with integralValue template parameter"
                    );
      return T{};
    }
    else
    {
      if constexpr(std::is_same_v<t_t, float>)
      {
        if constexpr(sizeof(t_t) != sizeof(BitsPatternfloat))
        {
          static_assert(sizeof(t_t) == sizeof(BitsPatternfloat),
                        "[eve::ieeeconstant] floating_point case - BitsPatternfloat has not the correct size");
          return T{};
        }
        else return static_cast<T>(bit_cast(BitsPatternfloat, as_<t_t>()));
      }
      else // if constexpr(std::is_same_v<t_t, double>)
      {
        if constexpr(sizeof(t_t) != sizeof(BitsPatterndouble))
        {
          static_assert(sizeof(t_t) == sizeof(BitsPatterndouble),
                        "[eve::ieeeconstant] floating_point case - BitsPatterndouble has not the correct size");
          return T{};
        }
        else return static_cast<T>(bit_cast(BitsPatterndouble, as_<t_t>()));
      }
    }
  }
}

#endif
