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
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!  @typedef pointer_alignment_v
  //!
  //!  @tparam T Type to process
  //!
  //!  **Required header**: `#include <eve/traits/alignment.hpp>`,
  //!                       `#include <eve/traits.hpp>`
  //!   @code{.cpp}
  //!
  //!   template<typename T>
  //!   inline constexpr std::size_t pointer_alignment_v = 0ULL;
  //!
  //!   template<typename T>
  //!   inline constexpr std::size_t pointer_alignment_v<T*> = alignof(T);
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename T>
  inline constexpr std::size_t pointer_alignment_v = 0ULL;

  template<typename T>
  inline constexpr std::size_t pointer_alignment_v<T*> = alignof(T); 
  
  template<typename T>
  inline constexpr std::size_t pointer_alignment_v<T const*> = alignof(T);


  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!  @typedef alignment_v
  //!
  //!  @tparam T Type to process
  //!
  //!  **Required header**: `#include <eve/traits/alignment.hpp>`,
  //!                       `#include <eve/traits.hpp>`
  //!   @code{.cpp}
  //!   template<typename T>
  //!   inline constexpr std::size_t alignment_v = alignof(T);
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename T>
  inline constexpr std::size_t alignment_v = alignof(T);

  template<typename T>
  inline constexpr std::size_t alignment_v<logical<T>> = alignof(T);

  template<typename T, typename Size>
  inline constexpr std::size_t alignment_v<wide<T,Size>> = wide<T,Size>::alignment(); 

  template<typename T, typename Size>
  inline constexpr auto alignment_v<logical<wide<T,Size>>> = logical<wide<T,Size>>::alignment();
}
