//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <cstddef>

namespace eve
{
  template<std::ptrdiff_t Cardinal> struct fixed;
  struct  scalar_cardinal;

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!   @struct cardinal
  //!   @brief Computes the cardinal of a given type
  //!
  //!   **Required header:** `#include <eve/traits/cardinal.hpp>`
  //!
  //!   For a given type `T`, computes the type of its cardinal.
  //!
  //!   @tparam T Type to process
  //!
  //!   #### Member types
  //!
  //!   |Name   | Definition               |
  //!   |:------|:-------------------------|
  //!   |`type` | The cardinal type of `T` |
  //!
  //!    <br/>
  //!
  //!   @groupheader{Helper types}
  //!
  //!   @code{.cpp}
  //!   template<typename Type>
  //!   using cardinal_t = typename cardinal<Type>::type;
  //!   @endcode
  //!
  //!   @groupheader{Helper variable template}
  //!
  //!   @code{.cpp}
  //!   template<typenale Type>
  //!   inline constexpr auto cardinal_v = cardinal<T>::value;
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename Type>
  struct cardinal : scalar_cardinal
  {
    using type = scalar_cardinal;
  };

  template<typename Type, typename Size>
  struct cardinal<wide<Type, Size>> : Size
  {
     using type = Size;
  };

  template<typename Type>
  struct cardinal<logical<Type>> : cardinal<Type>
  {
  };

  template<typename Type>
  using cardinal_t = typename cardinal<Type>::type;

  template<typename Type>
  inline constexpr auto cardinal_v = cardinal<Type>::value;
}
