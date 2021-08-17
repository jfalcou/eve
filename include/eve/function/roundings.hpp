//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  // Rounding decorator objects
  struct upward_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
    static const  auto value = 0x02 | 0x08; //_MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC;
  };

  struct downward_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
     static const auto value = 0x01 | 0x08; //_MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC;
  };

  struct to_nearest_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
    static const auto value = 0x00 | 0x08; // _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC;
  };

  struct toward_zero_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
    static const auto value = 0x03 | 0x08; // _MM_FROUND_TO_ZERO |_MM_FROUND_NO_EXC;
  };

  using upward_type      = decorated<upward_()>;
  using downward_type    = decorated<downward_()>;
  using to_nearest_type  = decorated<to_nearest_()>;
  using toward_zero_type = decorated<toward_zero_()>;

  inline constexpr upward_type      const upward       = {};
  inline constexpr downward_type    const downward     = {};
  inline constexpr to_nearest_type  const to_nearest   = {};
  inline constexpr toward_zero_type const toward_zero  = {};
}
