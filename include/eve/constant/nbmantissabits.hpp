//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONSTANT_NBMANTISSABITS_HPP_INCLUDED
#define EVE_CONSTANT_NBMANTISSABITS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  EVE_MAKE_CALLABLE(nbmantissabits_, nbmantissabits_);

  template<typename T>
  EVE_FORCEINLINE auto Nbmantissabits(as_<T> const & = {})
  {
    using t_t = detail::value_type_t<T>;
    using i_t = detail::as_integer_t<T>;
    if  constexpr(std::is_floating_point_v<t_t>)
    {
      if constexpr(std::is_same_v<t_t, float>) return i_t(23);
      if constexpr(std::is_same_v<t_t, double >) return i_t(52);
    }
    else
      return i_t(0);
  }

  EVE_MAKE_NAMED_CONSTANT(nbmantissabits_, Nbmantissabits);
}

#endif
