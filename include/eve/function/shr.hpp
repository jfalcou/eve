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
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup operators
  //! @{
  //! @var shr
  //!
  //! @brief Callable object performing the computation of the arithmetic right shift operation.
  //!
  //! **Required header:** `#include <eve/function/shr.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the arithmetic right shift operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, integral_real_value U > auto operator()( T x, U n ) const noexcept
  //!  requires bit_compatible< T, U >;
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
  //!Computes the [element-wise](../../../glossary.html#element-wise) arithmetic right shift of the first parameter by the second one.
  //!
  //!the call `shr(x, n)` is equivalent to `x << n` if `x`  is an  [simd value](../../concepts.html#value).
  //!
  //!The types must share the same cardinal or be scalar and if $N$ is the size in bits  of the element type of `T`,
  //!all  [elements](../../../glossary.html#element) of n must belong to the
  //!interval: `[0, N[` or the result is undefined.
  //!
  //!@warning  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::shr
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `shr[cond](x, ...)` is equivalent to `if_else(cond,shr(x, ...),x)`
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
  //! @include{lineno} doc/core/shr.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct shr_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::shr_), T const&, [[maybe_unused]] S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(s),
                  "[eve::shr] Shifting by " << s
                                            << " is out of the range [0, "
                                            << sizeof(value_type_t<T>) * 8
                                            << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(shr_, shr);

  namespace detail
  {
    template<integral_value T, integral_value U>
    EVE_FORCEINLINE auto shr_(EVE_SUPPORTS(cpu_), T a, U s) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return  static_cast<T>(a >> s);
      else if constexpr( scalar_value<T>)
      {
        using w_t = as_wide_t<T, cardinal_t<U>>;
                                                          return w_t(a) >>  s;
      }
      else                                                return a >> s;
    }
  }
}
