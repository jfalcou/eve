//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/traits/as_wide.hpp>
#include <eve/traits/iterator_cardinal.hpp>
#include <eve/traits/value_type.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @typedef wide_value_type_t
  //!
  //!  @tparam T Type to process
  //!
  //!  **Required header**: `#include <eve/traits/wide_value_type.hpp>`,
  //!                       `#include <eve/traits.hpp>`
  //!   @code{.cpp}
  //!   template<typename T>
  //!   using wide_value_type_t = as_wide_t<value_type_t<T>, iterator_cardinal_t<T>>
  //!   @endcode
  //! @}
  //================================================================================================

  template<typename T>
  using wide_value_type_t = as_wide_t<value_type_t<T>, iterator_cardinal_t<T>>;
}
