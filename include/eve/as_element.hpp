//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/traits/element_type.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
  //! @{
  //! @struct as_element
  //! @brief Lightweight type-wrapper over element type
  //!
  //! **Required header:** `#include <eve/as.hpp>`
  //!
  //! eve::as_element<T> is a short-cut for eve::as<eve::element_type_t<T>> designed to work with
  //! automatic type deduction.
  //!
  //! @tparam T Type to wrap
  //!
  //! @}
  //================================================================================================
  template<typename T>
  struct as_element : as<element_type_t<T>>
  {
    constexpr as_element()          noexcept {}
    constexpr as_element(T const&)  noexcept {}
  };
}
