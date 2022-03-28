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
  struct pedantic_;

  //================================================================================================
  // Function decorator - differential mode
  template<int Param> struct diff_
  {
    static constexpr auto combine( decorated<pedantic_()> const& ) noexcept
    {
      return decorated<diff_(pedantic_)>{};
    }
  };

  template<int Param> using diff_type = decorated<diff_<Param>()>;

  //================================================================================================
  //! @addtogroup core
  //! @{
  //!  @var diff
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  diff is an alias of [diff_1st](eve::diff_1st) and [diff_nth<1>](eve::diff_nth)
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
  //! @addtogroup core
  //! @{
  //!  @var diff_1st
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  diff_1st is an alias of [diff](eve::diff) and [diff_nth<1>](eve::diff_nth)
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
  //! @addtogroup core
  //! @{
  //!  @var diff_2nd
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  diff_2nd is an alias of [diff_nth<2>](eve::diff_nth)
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
  //! @addtogroup core
  //! @{
  //!  @var diff_3rd
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  diff_3rd is an alias of [diff_nth<3>](eve::diff_nth)
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
  //! @addtogroup core
  //! @{
  //!  @var diff_nth
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if diff_nth is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
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
  template<int N> inline constexpr diff_type<N> const diff_nth = diff_type<N>{};

}
