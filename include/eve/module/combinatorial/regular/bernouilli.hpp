//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
  //!   @brief Computes the nth bernouilli number \f$b_n\f$ as a double.
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
  //!      eve::as_wide_as<M, double> bernouilli(N n) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n` :  unsigned argument.
  //!
  //!    **Return value**
  //!
  //!    the value of the nth bernouilli number
  //!    is returned.
  //!
  //!    The result element type is always double to try to avoid overflow
  //!    and its cardinal is the same as the entry in case of an simd call.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/combinatorial/regular/bernouilli.cpp}
  //! @}
  //================================================================================================
  namespace tag { struct bernouilli_; }
  template<> struct supports_conditional<tag::bernouilli_> : std::false_type {};

  EVE_MAKE_CALLABLE(bernouilli_, bernouilli);
}

#include <eve/module/combinatorial/regular/impl/bernouilli.hpp>
