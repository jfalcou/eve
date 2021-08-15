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

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //!  @var diff
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff is to be applied to eve::fname then
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
  //! a @callable performing the partial derivative of the callable relative to its first parameter
  //!
  //!  @}
  //================================================================================================
  [[maybe_unused]] inline constexpr diff_type<1> const diff      = {};

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //!  @var diff_1st
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff is to be applied to eve::fname then
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
  //! a @callable performing the partial derivative of the callable relative to its first parameter
  //!
  //!  @}
  //================================================================================================
  [[maybe_unused]] inline constexpr diff_type<1> const diff_1st  = {};

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //!  @var diff_2nd
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff is to be applied to eve::fname then
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
  //! a @callable performing the partial derivative of the callable relative to its second parameter
  //!
  //!  @}
  //================================================================================================
  [[maybe_unused]] inline constexpr diff_type<2> const diff_2nd  = {};

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //!  @var diff_3rd
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff is to be applied to eve::fname then
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
  //! a @callable performing the partial derivative of the callable relative to its second parameter
  //!
  //!  @}
  //================================================================================================
  [[maybe_unused]] inline constexpr diff_type<3> const diff_3rd  = {};

  //================================================================================================
  //! @addtogroup decorator
  //! @{
  //!  @var diff_nth
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff_nth is to be applied to eve::fname then
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
  //!
  //!  - diff_nth<N> a @callable performing the derivative of the callable
  //!    relative to its N-th  parameter, N being a non-type template integer.
  //!
  //!  @}
  //================================================================================================
  template<auto N> inline constexpr diff_type<N> const diff_nth = diff_type<N>{};

}
