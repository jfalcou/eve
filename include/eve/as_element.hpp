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
    explicit constexpr as_element(T const&)  noexcept {}
  };
  
  template <typename T> using int_from        = as_element<as_integer_t<T, signed>>;
  template <typename T> using uint_from       = as_element<as_integer_t<T, unsigned>>;
  template <typename T> using floating_from   = as_element<as_floating_point_t<T>>;
  template <typename T> using upgraded_from   = detail::upgrade_t<element_type_t<T>>;
  template <typename T> using downgraded_from = detail::downgrade_t<element_type_t<T>>;
//   template <typename T> using to_int         = as_element<as_integer_t<T, signed>>;
//   template <typename T> using to_uint       = as_element<as_integer_t<T, unsigned>>;
//   template <typename T> using to_floating   = as_element<as_floating_point_t<T>>;
//   template <typename T> using to_upgraded   = detail::upgrade_t<element_type_t<T>>;
//   template <typename T> using to_downgraded = detail::downgrade_t<element_type_t<T>>;
}
