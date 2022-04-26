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
  // Function decorator - kfolderential mode
  template<auto Param> struct kfold_
  {
    template<auto K> static constexpr auto combine( decorated<pedantic_()> const& ) noexcept
    {
      return decorated<kfold_(pedantic_)>{};
    }
  };

  template<auto Param> using kfold_type = decorated<kfold_<Param>()>;

  //================================================================================================
  //! @addtogroup core
  //! @{
  //!  @var faith
  //!
  //! @brief  Higher-order @callable imbuing faithfull rounding semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if kfold is to be applied to eve::fname then
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve:module/core.hpp.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  must be included.
  //!
  //!  faith is an alias of  [kfold<0>](eve::kfold)
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
  //! a @callable performing the operation with faithfull rounding
  //!
  //!  @}
  //================================================================================================
  [[maybe_unused]] inline constexpr kfold_type<0> const faith      = {};


  //================================================================================================
  //! @addtogroup core
  //! @{
  //!  @var kfold
  //!
  //! @brief  Higher-order @callable imbuing K-fold computation semantics onto other @callable{s}.
  //!
  //! #### Synopsis
  //!
  //!  if kfold is to be applied to eve::fname then
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
  //!  - kfold<K>(f) a @callable performing f "as if" the computation was done with K-fold semantics
  //!
  //!  @}
  //================================================================================================
  template<auto N> inline constexpr kfold_type<N> const kfold = kfold_type<N>{};

}
