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
//!   @var lcm
//!   @brief Computes the least common multiple of the inputs.
//!
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
//!      template< eve::real_value T,  eve::real_value U >
//!      T lcm(T p, U n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   `p`, `n`:   [real arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    Returns the least common multiple of |p| and |n|.
//!
//!    @warning
//!    `p` and `n` can be of any [real values](@ref eve::value) type, but
//!    when the types are not integral
//!    the greatest common divisor is defined only if `p` and `n` element are
//!    [flint](@ref eve::is_flint). If any
//!    of the arguments is not flint the result is undefined.
//!
//!  @groupheader{Example}
//!
//!     @godbolt{doc/combinatorial/regular/lcm.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Optimized Conversion Call
//!
//!     If the input types are integral, the result is succeptible to overflow,
//!     but will never be greater than the product of the two
//!     input values which will be representable in the upgraded integral type:
//!
//!     The call `upgrade_(lcm)(a,b)` will then return a correct result in the upgraded type
//!     if the upgraded type is available.
//!
//!    **Example**
//!
//!       @godbolt{doc/combinatorial/conversion/lcm.cpp}
//!
//!  @}
//================================================================================================
namespace tag
{
  struct lcm_;
}

template<> struct supports_optimized_conversion<tag::lcm_> : std::true_type
{};

EVE_MAKE_CALLABLE(lcm_, lcm);
}

#include <eve/module/combinatorial/regular/impl/lcm.hpp>
