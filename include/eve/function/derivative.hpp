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

  [[maybe_unused]] inline constexpr diff_type<1> const diff      = {};
  [[maybe_unused]] inline constexpr diff_type<1> const diff_1st  = {};
  [[maybe_unused]] inline constexpr diff_type<2> const diff_2nd  = {};
  [[maybe_unused]] inline constexpr diff_type<3> const diff_3rd  = {};
  template<auto N> inline constexpr diff_type<N> const diff_nth = diff_type<N>{};

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //!  @var diff
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  diff can be declined in
  //!  diff,
  //!  diff_1st,
  //!  diff_2nd,
  //!  diff_3rd,
  //!  diff_nth<N> where N is an integer non type template parameter.
  //!
  //!  if any of these decorators is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/diff/fname.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //! #### Members Functions
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::callable auto const& f ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! @param f
  //! An instance of eve::callable
  //!
  //! @return
  //!  - For diff and diff_1st a @callable performing the derivative of the callable relative to its first parameter
  //!  - For diff_2nd a @callable performing the derivative of the callable relative to its second parameter
  //!  - For diff_3rd a @callable performing the derivative of the callable relative to its third  parameter
  //!  - For diff_nth<N> a @callable performing the derivative of the callable relative to its N-th  parameter
  //!
  //! The eve::callable must provide enough parameters.
  //!  @}
  //================================================================================================
}
