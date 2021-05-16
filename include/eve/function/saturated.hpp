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
  // Function decorators mark-up used in function overloads
  struct saturated_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using saturated_type = decorated<saturated_()>;

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //! @var saturated
  //!
  //! #### Synopsis
  //!
  //! **Required header:** `#include <eve/function/saturated.hpp>`
  //!
  //! Higher-order @callable imbuing saturation semantic onto other @callable{s}.
  //!
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation but while taking care of saturating
  //! its return value so that it always fit into the input type range.
  //!
  //!  @}
  //================================================================================================
  inline constexpr saturated_type const saturated = {};
}
