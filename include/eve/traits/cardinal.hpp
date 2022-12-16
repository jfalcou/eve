//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <cstddef>

namespace eve
{
  template<std::ptrdiff_t Cardinal> struct fixed;

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
  //!   template<typename Type>
  //!   inline constexpr auto cardinal_v = cardinal<Type>::value;
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename Type>
  struct cardinal : fixed<1>
  {};

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
