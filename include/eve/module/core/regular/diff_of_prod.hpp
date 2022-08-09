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
//! @addtogroup core_accuracy
//! @{
//!   @var diff_of_prod
//!   @brief Computes the difference of products operation with better accuracy
//!   than the naive formula.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T
//!              , eve::floating_value U
//!              , eve::floating_value V
//!              , eve::floating_value W>
//!      T diff_of_prod(T x, U y, V z, W t ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`, `t`:  [floating value arguments](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!    The value of `x*y-z*t`,  with better precision if correct fma is available,
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/diff_of_prod.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * eve::raw
//!
//!     The call `eve::raw(eve::diff_of_prod)(x, y, z, t)` computes a raw
//!     version of eve::diff_of_prod,  i.e. the naive formula
//!
//!   * eve::pedantic
//!
//!     The call `eve::pedantic(eve::diff_of_prod)(x, y, z, t)` computes a pedantic
//!     version of eve::diff_of_prod ensuring better accuracy in any case.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/pedantic/diff_of_prod.cpp}
//!
//! @}
//================================================================================================

namespace tag
{
  struct diff_of_prod_;
}
template<> struct supports_conditional<tag::diff_of_prod_> : std::false_type
{};

EVE_MAKE_CALLABLE(diff_of_prod_, diff_of_prod);
}

#include <eve/module/core/regular/impl/diff_of_prod.hpp>
