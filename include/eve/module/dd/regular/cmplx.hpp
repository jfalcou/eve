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
  struct cmplx_
  {
    template<typename D> static constexpr auto combine( D const& ) noexcept =delete;
  };

  using cmplx_type = decorated<cmplx_()>;
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var cmplx
  //!
  //! @brief  Higher-order @callable imbuing complex computation  return onto other @callable{s}
  //! using floating real entries.
  //!
  //! #### Synopsis
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
  //! A @callable performing the same kind of operation but while insuring to return
  //! cmplx values.
  //!
  //!  @}
  //================================================================================================
  inline constexpr cmplx_type const cmplx = {};
}
