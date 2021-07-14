//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/function/abs.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup operators
  //! @{
  //! @var rshr
  //!
  //! @brief Callable object computing the arithmetic left/right shift operation according to shift sign.
  //!
  //! **Required header:** `#include <eve/function/rshr.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the arithmetic left/right shift operation according to shift sign   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, integral_real_value U > auto operator()( T x, U n ) const noexcept requires bit_compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //!`n`:   [integral value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Computes the [element-wise](../../../glossary.html#element-wise) arithmetic left/right shift of the first parameter by the second one.
  //!
  //!the call `rshr(x, n)` is equivalent to `if_else(n>0, shl(x, n), shr(x, n))` if `x`  is an  [simd value](../../concepts.html#value).
  //!
  //!The types must share the same cardinal or be scalar and if $N$ is the size in bits  of the element type of `T`,
  //!all  [elements](../../../glossary.html#element) of n must belong to the
  //!interval: `[-N, N[` or the result is undefined.
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::rshr
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `rshr[cond](x, ...)` is equivalent to `if_else(cond,rshr(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/rshr.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct rshr_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rshr_), T const& , [[ maybe_unused ]] S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(eve::abs(s)),
                  "[eve::rshr] - Shifting by " << s
                  << " is out of the range ]"
                  << -sizeof(value_type_t<T>) * 8
                  << ", "
                  << sizeof(value_type_t<T>) * 8
                  << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(rshr_, rshr);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/rshr.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/rshr.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/rshr.hpp>
#endif
