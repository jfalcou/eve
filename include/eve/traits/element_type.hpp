//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
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
  struct element_type
  {
    using type = T;
  };

  template<typename T, typename N>             struct element_type<wide<T,N>>   { using type = T; };
  template<typename T>                         struct element_type<wide<T>>     { using type = T; };

  template<typename T>
  struct element_type<logical<T>>     { using type = logical<typename element_type<T>::type>; };

  template<typename T>
  using element_type_t = typename element_type<T>::type;
}
