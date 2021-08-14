//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var sqrt
  //!
  //! @brief Callable object computing the square root.
  //!
  //! **Required header:** `#include <eve/function/sqrt.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the square root   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](../../../glossary.html#elment-wise) square root  of the input.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::sqrt
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `sqrt[cond](x, ...)` is equivalent to `if_else(cond,sqrt(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::raw
  //!     The call `raw(sqrt)(x)`, call a proper system intrinsic if one exists, but with possibly very poor accuracy in return.
  //!      Otherwise it uses the [`regular`](../decorators.html#regular) call.
  //!  
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/sqrt.hpp>`
  //!  
  //!     The expression `diff(sqrt)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/sqrt.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag
  {
    struct sqrt_;
  }

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::sqrt_), [[maybe_unused]] T const &v)
    {
      if constexpr( std::is_integral_v<T> && std::is_signed_v<T> )
      {
        EVE_ASSERT(v >= 0, "[eve::sqrt] - Invalid parameter: " << v);
      }
    }
  }

  EVE_MAKE_CALLABLE(sqrt_, sqrt);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/sqrt.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/sqrt.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/sqrt.hpp>
#endif
