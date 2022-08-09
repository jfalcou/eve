//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var prime_floor
//!   @brief Returns the the greatest prime less or equal to the input.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/combinatorial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::unsigned_value N >
//!      N prime_floor(N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  unsigned argument. If `n` is greater than 104'729, behavior is undefined.
//!
//!   **Return value**
//!   The greatest prime less or equal to `n`.
//!   The result type is the same as the input one unless a converter is applied (see below).
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/combinatorial/regular/prime_floor.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Optimized Conversion Call
//!
//!     The converters eve::float_,  eve::double_, eve::floating_ can be applied to
//!     produce a floating point output.
//!
//!    **Example**
//!
//!    @godbolt{doc/combinatorial/conversion/prime_floor.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct prime_floor_;
}

template<> struct supports_optimized_conversion<tag::prime_floor_> : std::true_type
{};

EVE_MAKE_CALLABLE(prime_floor_, prime_floor);
}

#include <eve/module/combinatorial/regular/impl/prime_floor.hpp>
