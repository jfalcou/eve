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
  //================================================================================================
  // Rounding decorator objects
  struct restricted_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  struct small_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  struct medium_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  struct big_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using restricted_type = decorated<restricted_()>;
  using small_type      = decorated<small_()>;
  using medium_type     = decorated<medium_()>;
  using big_type        = decorated<big_()>;

  inline constexpr restricted_type  const restricted  = {};
  inline constexpr small_type       const small       = {};
  inline constexpr medium_type      const medium      = {};
  inline constexpr big_type         const big         = {};
}
