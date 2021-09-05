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
  struct q_kind_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using q_kind_type = decorated<q_kind_()>;
  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //! @var q_kind
  //!
  //! @brief  Higher-order @callable imbuing q_kind behaviour onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the q_kind algorithm choice
  //!
  //!  @}
  //================================================================================================
  inline constexpr q_kind_type const q_kind = {};
}
