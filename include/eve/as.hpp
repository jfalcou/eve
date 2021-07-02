//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve
{
  //================================================================================================
  //! @addtogroup utility
  //! @{
  //! @struct as
  //! @brief Lightweight type-wrapper
  //!
  //! **Required header:** `#include <eve/as.hpp>`
  //!
  //! Wraps type into a constexpr, trivially constructible empty class to optimize passing type
  //! parameters via object instead of via template parameters
  //!
  //! @tparam T Type to wrap
  //!
  //! @}
  //================================================================================================
  template<typename T>
  struct as
  {
    //! @brief Wrapped type
    using type = T;

    constexpr as()          noexcept {}
    constexpr as(T const&)  noexcept {}
  };
}
