//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/ifrexp.hpp>

namespace eve
{
template<typename Options>
struct frexp_t : elementwise_callable<frexp_t, Options, pedantic_option, raw_option>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(frexp_t, frexp_);
};

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var frexp
//!   @brief `tuple_callable` computing the ieee  pair of mantissa and exponent of a floating value,
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
//!      template< eve::floating_value T >  eve::zipped<T,T> frexp(T x) noexcept;           //1
//!      template< eve::floating_value T >  eve::zipped<T,T> frexp[pedantic](T x) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [floating value](@ref floating_value).
//!
//!   **Return value**
//!
//!     1. returns a kumi::tuple `{m,e}`  of values ` of the same type as `x`, which are related by
//!       \f$x =  m\times 2^e\f$, with  \f$|m| \in [0.5, 1.5[\f$.
//!       However, the cases \f$x = \pm\infty\f$ or is a Nan or a denormal are undefined.
//!
//!     2. the pedanic option takes also properly care of the cases where
//!        \f$x = \pm0, \pm\infty\f$ or is a Nan, where \f$m=x\f$ and \f$e=0\f$ and of the
//!        denormal cases.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/frexp)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/frexp.cpp}
//! @}
//================================================================================================
inline constexpr auto frexp = functor<frexp_t>;

namespace detail
{
template<typename T, callable_options O>
EVE_FORCEINLINE constexpr auto frexp_(EVE_REQUIRES(cpu_), O const& o, T const& a0) noexcept
{
  auto [m, e] = ifrexp[o](a0);
  return eve::zip(m, convert(e,as_element<T>{}));
}

}}
