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
  // Function decorator - deriverential mode
  template<int Param> struct deriv_
  {
    static constexpr auto combine( decorated<pedantic_()> const& ) noexcept
    {
      return decorated<deriv_(pedantic_)>{};
    }
  };

  template<int Param> using deriv_type = decorated<deriv_<Param>()>;

  //================================================================================================
  //! @addtogroup core
  //! @{
  //!  @var deriv
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if deriv is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  deriv is an alias of [deriv_1st](eve::deriv_1st) and [deriv_nth<1>](eve::deriv_nth)
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
  [[maybe_unused]] inline constexpr deriv_type<1> const deriv      = {};

  //================================================================================================
  //! @addtogroup core
  //! @{
  //!  @var deriv_1st
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if deriv is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  deriv_1st is an alias of [deriv](eve::deriv) and [deriv_nth<1>](eve::deriv_nth)
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
  [[maybe_unused]] inline constexpr deriv_type<1> const deriv_1st  = {};

  //================================================================================================
  //! @addtogroup core
  //! @{
  //!  @var deriv_2nd
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if deriv is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  deriv_2nd is an alias of [deriv_nth<2>](eve::deriv_nth)
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
  [[maybe_unused]] inline constexpr deriv_type<2> const deriv_2nd  = {};

  //================================================================================================
  //! @addtogroup core
  //! @{
  //!  @var deriv_3rd
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if deriv is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  deriv_3rd is an alias of [deriv_nth<3>](eve::deriv_nth)
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
  [[maybe_unused]] inline constexpr deriv_type<3> const deriv_3rd  = {};

  //================================================================================================
  //! @addtogroup core
  //! @{
  //!  @var deriv_nth
  //!
  //! @brief  Higher-order @callable imbuing derivative semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if deriv_nth is to be applied to eve::fname then
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
  //!  - deriv_nth<N> a @callable performing the derivative of the callable
  //!    relative to its N-th  parameter, N being a non-type template integer.
  //!
  //!  @}
  //================================================================================================
  template<int N> inline constexpr deriv_type<N> const deriv_nth = deriv_type<N>{};

}
