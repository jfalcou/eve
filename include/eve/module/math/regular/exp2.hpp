//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/all.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup exponential
  //! @{
  //! @var exp2
  //!
  //! @brief Callable object computing \f$2^x\f$.
  //!
  //! **Required header:** `#include <eve/function/exp2.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | computes the base 2 exponential                            |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( real_value x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [real value](@ref eve::real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) exponential of base 2 of the input.
  //!In particular, for floating inputs:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned
  //!   * If the element is \f$-\infty\f$, \f$+0\f$ is returned
  //!   * If the element is \f$\infty\f$, \f$\infty\f$ is returned
  //!   * If the element is a `NaN`, `NaN` is returned
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::exp2
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `exp2[cond](x, ...)` is equivalent to `if_else(cond,exp2(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported converters
  //!
  //!  * eve::float_,  eve::double_, eve::floating_
  //!
  //!     The expression `d(exp2)(x)` where d in one of these 3 converters is supported if x is an
  //!     [integral value](@ref eve::integral_value) and produce a floating point output.
  //!
  //! #### Supported decorators
  //!
  //!  * eve::saturated
  //!
  //!     The expression `saturated(exp2)(x)` saturate the output if `x`
  //!     is an [integral value](@ref eve::integral_value).
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/exp2.hpp>`
  //!
  //!     The expression `diff(exp2)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/exp2.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct exp2_; }

  template<>
  struct supports_optimized_conversion<tag::exp2_> : std::true_type {};

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::exp2_), T const& ,  [[maybe_unused]] S const& s)
    {
      using vt_t = element_type_t<T>;
      if constexpr(std::is_integral_v<vt_t>)
      {
        EVE_ASSERT( eve::all(is_gez(s)),
                    "[eve::exp2] - with integral entries the parameter element(s) must be greater than 0"
                  );
        EVE_ASSERT( eve::all(is_less(s, sizeof(vt_t)*8-std::is_signed_v<vt_t>)),
                    "[eve::exp2]  - overflow caused by too large integral entry"
                  );
      }
    }
  }

  EVE_MAKE_CALLABLE(exp2_, exp2);
}

#include <eve/module/math/regular/impl/exp2.hpp>
