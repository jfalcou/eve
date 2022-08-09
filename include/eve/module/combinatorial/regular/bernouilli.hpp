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
//!   @var bernouilli
//!   @brief Computes the nth Bernouilli number \f$b_n\f$ as a double.
//!
//!   **Defined in header**
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
//!      eve::as_wide_as<double, N> bernouilli(N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  unsigned argument.
//!
//!    **Return value**
//!
//!    The value of the nth Bernouilli number is returned.
//!    The result's element type is double to avoid overflow and its cardinal is the same as 'n'.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/combinatorial/regular/bernouilli.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct bernouilli_;
}
template<> struct supports_conditional<tag::bernouilli_> : std::false_type
{};

EVE_MAKE_CALLABLE(bernouilli_, bernouilli);
}

#include <eve/module/combinatorial/regular/impl/bernouilli.hpp>
