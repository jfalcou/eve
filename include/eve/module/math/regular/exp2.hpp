//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup math_exp
//! @{
//! @var exp2
//!
//! @brief Callable object computing \f$2^x\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T exp2(T x) noexcept;                                     //1
//!
//!      template< eve::floating_value T >
//!      eve::complex<T> exp10(eve::complex<T> z) noexcept;        //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   * `x`:   [real value](@ref eve::real_value).
//!   * `z`:   [complex ](@ref eve::complex) argument.
//!
//! **Return value**
//!
//!   Returns the [elementwise](@ref glossary_elementwise) exponential of base 2 of the input.
//!   In particular, for floating inputs:
//!
//!     * If the element is \f$\pm0\f$, \f$1\f$ is returned
//!     * If the element is \f$-\infty\f$, \f$+0\f$ is returned
//!     * If the element is \f$\infty\f$, \f$\infty\f$ is returned
//!     * If the element is a `NaN`, `NaN` is returned
//!
//!   2. Returns [elementwise](@ref glossary_elementwise) the exponential of base 10 of the input as if computed
//!      by `eve::exp (eve::log_2(as(z))*z)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/exp2.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::exp2[mask](x)` provides a masked version of `eve::exp2` which is
//!     equivalent to `if_else (mask, exp2(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/exp2.cpp}
//!  @}
//================================================================================================
namespace tag
{
  struct exp2_;
}

template<> struct supports_optimized_conversion<tag::exp2_> : std::true_type
{};

namespace detail
{
  template<typename T, typename S>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::exp2_), T const&, [[maybe_unused]] S const& s)
  {
    using vt_t = element_type_t<T>;
    if constexpr( std::is_integral_v<vt_t> )
    {
      EVE_ASSERT(
          eve::all(is_gez(s)),
          "[eve::exp2] - with integral entries the parameter element(s) must be greater than 0");
      EVE_ASSERT(eve::all(is_less(s, sizeof(vt_t) * 8 - std::is_signed_v<vt_t>)),
                 "[eve::exp2]  - overflow caused by too large integral entry");
    }
  }
}

EVE_MAKE_CALLABLE(exp2_, exp2);
}

#include <eve/module/math/regular/impl/exp2.hpp>
