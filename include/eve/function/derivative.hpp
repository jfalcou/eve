//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  struct pedantic_;

  //================================================================================================
  // Function decorator - derivative mode
  template<auto Param> struct derivative_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;

    template<auto N> static constexpr auto combine( decorated<pedantic_> const& ) noexcept
    {
      return decorated<derivative_(pedantic_)>{};
    }
  };

  template<auto Param> using derivative_type = decorated<derivative_<Param>()>;

  inline constexpr derivative_type<1> const derivative = {};
  inline constexpr derivative_type<1> const derivative_1st = {};
  inline constexpr derivative_type<2> const derivative_2nd = {};
  inline constexpr derivative_type<3> const derivative_3rd = {};
  template < auto N > inline constexpr derivative_type<N> const deriv = derivative_type<N>{};

}
