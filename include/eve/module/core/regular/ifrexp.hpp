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
  //! @addtogroup core_internal
  //! @{
  //!   @var ifrexp
  //!   @brief Computes the [elementwise](@ref glossary_elementwise) ieee
  //!   pair of mantissa and exponent of the floating value,
  //!
  //!   $details$
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
  //!      kumi::tuple<T, eve::as_integer<T>> ifrexp(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!   **Return value**
  //!
  //!     Computes the [elementwise](@ref glossary_elementwise) ieee ifrexp of the floating value,
  //!     returning a pair `{m,e}`  of values `m` being of the same type as `x` and `e` of
  //!     the associated integral type, which are related by
  //!     \f$x =  m\times 2^e\f$, with  \f$|m| \in [0.5, 1.5[\f$.
  //!
  //!     However, the cases \f$x = \pm\infty\f$ or is a Nan or a denormal are undefined.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/ifrexp.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * eve::pedantic
  //!
  //!     The call `eve::pedantic(eve::ifrexp)(x)` takes also properly care of the cases where
  //!     \f$x = \pm0, \pm\infty\f$ or is a Nan, where \f$m=x\f$ and \f$e=0\f$ and of the
  //!     denormal cases.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/saturated/abs.cpp}
  //! @}
  //================================================================================================

  namespace tag { struct ifrexp_; }
  template<> struct supports_conditional<tag::ifrexp_> : std::false_type {};

  EVE_MAKE_CALLABLE(ifrexp_, ifrexp);
}

#include <eve/module/core/regular/impl/ifrexp.hpp>
