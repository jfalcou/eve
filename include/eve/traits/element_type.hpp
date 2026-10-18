//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <eve/traits/translation.hpp>
#include <type_traits>

namespace eve
{
  namespace _
  {
    template<typename T>
    extern T element_type;

    template<typename T, typename N> 
    extern T element_type<wide<T,N>>;

    template<typename T> 
    extern T element_type<wide<T>>;

    template<typename T>
    extern logical<decltype(element_type<T>)> element_type<logical<T>>;
  }
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @struct element_type
  //!   @brief Extracts the scalar part of a type
  //!
  //!   **Required header:** `#include <eve/traits/element_type.hpp>`
  //!
  //!   For a given type `T`, computes the type of its inner elements.
  //!
  //!   @tparam T Type to process
  //!
  //!   #### Member types
  //!
  //!   |Name   | Definition                           |
  //!   |:------|:-------------------------------------|
  //!   |`type` | The type of element contained in `T` |
  //!
  //!    <br/>
  //!    #### Helper types
  //!
  //!    @code{.cpp}
  //!    template<typename Type>
  //!    using element_type_t = typename element_type<Type>::type;
  //!    @endcode
  //! @}
  //================================================================================================
  template<typename T>
  using element_type_t = decltype(_::element_type<std::remove_cvref_t<T>>);

  // Translate an element_type directly
  template <typename T>
  using translated_element_type_t = translate_t<element_type_t<T>>;
}
