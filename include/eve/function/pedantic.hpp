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
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct pedantic_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using pedantic_type = decorated<pedantic_()>;

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //! @var pedantic
  //!
  //! @brief  Higher-order @callable imbuing more standard semantic onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if pedantic(eve::fname) is to be called then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/pedantic/fname.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //! A @callable performing the same kind of operation but while insuring compatibility with
  //! the standard in corner cases, whenever possible.
  //!
  //!  @}
  //================================================================================================
  inline constexpr pedantic_type const pedantic = {};
}
