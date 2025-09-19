//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits/element_type.hpp>
#include <eve/traits/overload/supports.hpp>
#include <eve/concept/simd.hpp>

namespace eve
{
    //==================================================================================================================
  //! @addtogroup traits
  //! @{
  //!   @struct comparisons
  //!   @brief Extension point for ordering and equality computation
  //!
  //!   **Required header:** `#include <eve/traits/comparisons.hpp>`
  //!
  //!   eve::comparisons is an extension point for user-defined product type that may requires specific equality or
  //!   ordering computations. It is meant to be specialized on scalar user-defined type to provide a set of class
  //!   function members performing said operations.
  //!
  //!   To be considered valid, a specialization of eve::comparisons should provide either/or :
  //!     + Functions called `equal` and `not_equal` that take an eve::callable_options and two values of the
  //!       product type.
  //!     + Functions called `less`, `less_equal`, `greater`  and `greater_equal` that take an
  //!       eve::callable_options and two values of the product type
  //!
  //!   Depending on the set of functions provided, said type will be said to satisfy either the
  //!   eve::has_equality_support and/or the eve::has_ordering_support concept.
  //!
  //!   @tparam T Type to process
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/traits/comparisons.cpp}
  //! @}
  //====================================================================================================================
  template<typename T> struct comparisons;

  template<simd_value T>
  struct comparisons<T> : comparisons<element_type_t<T>>
  {};

  namespace detail
  {
    template <typename T>
    struct supports_equality {
      static constexpr bool has_eq = requires(T a, T b) { comparisons<element_type_t<T>>::equal(a, b); };
      static constexpr bool has_ne = requires(T a, T b) { comparisons<element_type_t<T>>::not_equal(a, b); };

      static_assert(has_eq == has_ne,
        "Either both or none of eve::comparisons::equal and eve::comparisons::not_equal must be provided");

      static constexpr bool value = has_eq && has_ne;
    };
  }

  template<typename T>
  inline constexpr bool has_equality_support = detail::supports_equality<T>::value;
}
