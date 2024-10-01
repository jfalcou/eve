//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/zip.hpp>

namespace eve
{
template<typename Options>
struct ifrexp_t : strict_elementwise_callable<ifrexp_t, Options, pedantic_option, raw_option>
{
  template<floating_value T>
  constexpr EVE_FORCEINLINE zipped<T, as_integer_t<T>> operator()(T v) const
  {
    return EVE_DISPATCH_CALL_PT((as<zipped<T, as_integer_t<T>>>{}), v);
  }

  EVE_CALLABLE_OBJECT(ifrexp_t, ifrexp_);
};

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var ifrexp
//!   @brief Computes the [elementwise](@ref glossary_elementwise) ieee
//!   pair of mantissa and exponent of the floating value,
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto ifrexp(floating_value auto x)                          noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto ifrexp[pedantic](floating_value x)                     noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref value).
//!
//!   **Return value**
//!
//!     1. Computes the [elementwise](@ref glossary_elementwise) ieee ifrexp of the floating value,
//!        returning a pair `{m,e}`  of values `m` being of the same type as `x` and `e` of
//!        the associated integral type, which are related by
//!        \f$x =  m\times 2^e\f$, with  \f$|m| \in [0.5, 1.5[\f$.
//!        However, the cases \f$x = \pm\infty\f$ or is a Nan or a denormal are undefined.
//!     2. This call takes also properly care of the cases where
//!        \f$x = \pm0, \pm\infty\f$ or is a Nan, where \f$m=x\f$ and \f$e=0\f$ and of the
//!        denormal cases.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/ifrexp.cpp}
//================================================================================================
  inline constexpr auto ifrexp = functor<ifrexp_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/ifrexp.hpp>
