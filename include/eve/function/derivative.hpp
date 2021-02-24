//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  struct pedantic_;

  //================================================================================================
  // Function decorator - differential mode
  template<auto Param> struct diff_
  {
    template<auto N> static constexpr auto combine( decorated<pedantic_()> const& ) noexcept
    {
      return decorated<diff_(pedantic_)>{};
    }
  };

  template<auto Param> using diff_type = decorated<diff_<Param>()>;

  inline constexpr diff_type<1> const diff      = {};
  inline constexpr diff_type<1> const diff_1st  = {};
  inline constexpr diff_type<2> const diff_2nd  = {};
  inline constexpr diff_type<3> const diff_3rd  = {};
  template<auto N> inline constexpr diff_type<N> const diff_nth = diff_type<N>{};
}
