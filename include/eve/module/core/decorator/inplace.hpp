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
  template<auto Param> struct diff_;

  //================================================================================================
  // Function decorators mark-up used in function overloads
  //================================================================================================
  struct inplace_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using inplace_type = decorated<inplace_()>;
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var inplace
  //!
  //! @brief  Higher-order @callable imbuing inplace  semantic onto other @callable{s} whenever possible.
  //!
  //! #### Synopsis
  //!
  //!  if inplace(eve::fname) is to be called then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/module/corenu.hpp>
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
  //! A @callable performing the same kind of operation but using the input
  //! parameter to store the output, whenever possible.
  //!
  //!  @}
  //================================================================================================
  [[maybe_unused]] inline constexpr inplace_type const inplace = {};
}
