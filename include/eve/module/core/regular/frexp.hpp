//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var frexp
//!   @brief Computes the [elementwise](@ref glossary_elementwise) ieee
//!   pair of mantissa and exponent of the floating value,
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
//!      template< eve::floating_value T >
//!      kumi::tuple<T, T> frexp(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes the [elementwise](@ref glossary_elementwise) ieee frexp of the floating value,
//!     returning a pair `{m,e}`  of values ` of the same type as `x`, which are related by
//!     \f$x =  m\times 2^e\f$, with  \f$|m| \in [0.5, 1.5[\f$.
//!
//!     However, the cases \f$x = \pm\infty\f$ or is a Nan or a denormal are undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/frexp.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * eve::pedantic
//!
//!     The call `eve::pedantic(eve::frexp)(x)` takes also properly care of the cases where
//!     \f$x = \pm0, \pm\infty\f$ or is a Nan, where \f$m=x\f$ and \f$e=0\f$ and of the
//!     denormal cases.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/pedantic/frexp.cpp}
//! @}
//================================================================================================

namespace tag
{
  struct frexp_;
}
template<> struct supports_conditional<tag::frexp_> : std::false_type
{};

EVE_MAKE_CALLABLE(frexp_, frexp);
}

#include <eve/module/core/regular/impl/frexp.hpp>
