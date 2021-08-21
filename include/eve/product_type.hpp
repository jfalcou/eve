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
  //!   @tparam Type  Type to register as supporting ordering operators
  //! @}
  //================================================================================================
  template<typename Type> struct supports_ordering : std::true_type
  {};

  //================================================================================================
  //! @addtogroup concepts
  //! @{
  //!   @var generator
  //!   The concept `ordered_structure<Type>` is satisfied if `Type` satisfies eve::product_type
  //!   and `supports_ordering<element_type_t<Type>>::value` evaluates to `true`.
  //! @}
  //================================================================================================
  template<typename Type>
  concept ordered_structure =     product_type<element_type_t<Type>>
                              &&  supports_ordering<element_type_t<Type>>::value;

  template<typename LHS, typename RHS>
  EVE_FORCEINLINE auto operator<(LHS const& a, RHS const& b) noexcept
  requires( same_value_type<LHS,RHS> && ordered_structure<LHS> && ordered_structure<RHS> )
  {
    return kumi::to_tuple(a) < kumi::to_tuple(b);
  }

  template<typename LHS, typename RHS>
  EVE_FORCEINLINE auto operator<= ( LHS const& a, RHS const& b) noexcept
  requires( same_value_type<LHS,RHS> && ordered_structure<LHS> && ordered_structure<RHS> )
  {
    return kumi::to_tuple(a) <= kumi::to_tuple(b);
  }

  template<typename LHS, typename RHS>
  EVE_FORCEINLINE auto operator> ( LHS const& a, RHS const& b) noexcept
  requires( same_value_type<LHS,RHS> && ordered_structure<LHS> && ordered_structure<RHS> )
  {
    return kumi::to_tuple(a) > kumi::to_tuple(b);
  }

  template<typename LHS, typename RHS>
  EVE_FORCEINLINE auto operator>= ( LHS const& a, RHS const& b) noexcept
  requires( same_value_type<LHS,RHS> && ordered_structure<LHS> && ordered_structure<RHS> )
  {
    return kumi::to_tuple(a) >= kumi::to_tuple(b);
  }
}
