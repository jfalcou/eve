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
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct raw_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using raw_type = decorated<raw_()>;
  //================================================================================================
  //! @addtogroup core_decorators
  //! @{
  //! @var raw
  //!
  //! @brief  Higher-order @callable imbuing quick and dirty behaviour onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation but using quick and dirty version whenever
  //! available.
  //!
  //! @warning using this decorator can imply loss of accuracy.
  //!
  //!  @}
  //================================================================================================
  inline constexpr raw_type const raw = {};
}
