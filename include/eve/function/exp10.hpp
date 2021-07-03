//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/assert.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/maxlog10.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup exponential
  //! @{
  //! @var exp10
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/exp10.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the  computation of exp10.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of exp10   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T> auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](../../concepts.html#value).
  //!
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](../../../glossary.html#elment-wise) exponential of base 10 of the input.
  //!In partucular, for floating inputs:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned
  //!   * If the element is \f$-\infty\f$, \f$+0\f$ is returned
  //!   * If the element is \f$\infty\f$, \f$\infty\f$ is returned
  //!   * If the element is a `NaN`, `NaN` is returned
  //!
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::exp10
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `exp10[cond](x, ...)` is equivalent to `if_else(cond,exp10(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/exp10.hpp>
  //! 
  //!  
  //!     The expression `diff(exp10)(x)` computes the derivative of the function at `x`.
  //!  
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/exp10.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct exp10_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::exp10_), T const&, [[maybe_unused]] S const& s)
    {
      using vt_t = value_type_t<T>;
      if constexpr(std::is_integral_v<vt_t>)
      {
        EVE_ASSERT( eve::all(is_gez(s)),
                    "[eve::exp10] - with integral entries the parameter element(s) must be greater then 0"
                  );
        EVE_ASSERT( eve::all(is_less(s, maxlog10(eve::as<T>()))),
                    "[eve::exp10]  - overflow caused by too large integral entry"
                  );
      }
    }
  }

  EVE_MAKE_CALLABLE(exp10_, exp10);
}

#include <eve/module/real/math/function/regular/generic/exp10.hpp>
