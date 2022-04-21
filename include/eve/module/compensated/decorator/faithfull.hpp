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
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct faitfull_
  {
    template<auto N> static constexpr auto combine( decorated<diff_<N>()> const& ) noexcept
    {
      return decorated<diff_<N>(faitfull_)>{};
    }
  };

  using faitfull_type = decorated<faitfull_()>;
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var faitfull
  //!
  //! @brief  Higher-order @callable imbuing more standard semantic onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if faitfull(eve::fname) is to be called then
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
  //! A @callable performing the same kind of operation but ensuring faifull rounding acuracy.
  //! I.E. computing the result as if it was the nearest rounding of the infinite precision computation.
  //!
  //!  @}
  //================================================================================================
  [[maybe_unused]] inline constexpr faitfull_type const faitfull = {};
}
