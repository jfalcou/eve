//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/traits/element_type.hpp>
#include <type_traits>

//==================================================================================================
//! @addtogroup utility
//! @{
//! @defgroup struct Structured Types Management
//!
//! **EVE** provides various elements to simplify the management of user-defined structures
//! as vectorized types.
//!
//! **Convenience header:** @code{.cpp} #include <eve/product_type.hpp> @endcode
//!
//! @}
//==================================================================================================

namespace eve
{
  //================================================================================================
  // Reinject kumi concept & traits in EVE
  using kumi::product_type;
  using kumi::is_product_type;

  //================================================================================================
  //! @addtogroup struct
  //! @{
  //!   @struct supports_ordering
  //!   @brief  Register a user-defined type to supports ordering
  //!
  //!   @tparam Type  Type to register as supporting ordering operators
  //!
  //!   ### Helper variable template
  //!
  //!   @code
  //!   template<typename Type>
  //!   inline constexpr bool supports_ordering_v = eve::supports_ordering<Type>::value;
  //!   @endcode
  //!
  //! @}
  //================================================================================================
  template<typename Type> struct supports_ordering : std::true_type
  {};

  template<typename Type>
  inline constexpr bool supports_ordering_v = supports_ordering<Type>::value;
}
