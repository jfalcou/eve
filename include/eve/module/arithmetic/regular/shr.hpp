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
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup operators
  //! @{
  //! @var shr
  //!
  //! @brief Callable object computing the arithmetic right shift operation.
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
  //!`x`:   [value](@ref eve::value).
  //!
  //!`n`:   [integral value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes the [elementwise](@ref glossary_elementwise) arithmetic right shift of the first parameter by the second one.
  //!
  //!the call `shr(x, n)` is equivalent to `x << n` if `x`  is an  [simd value](@ref eve::simd_value).
  //!
  //!The types must share the same cardinal or be scalar and if `N` is the size in bits  of the element type of `T`,
  //!all  [elements](@ref glossary_elementwise) of n must belong to the
  //!interval: `[0, N[` or the result is undefined.
  //!
  //!  @warning
  //!     Although the infix notation with `>>` is supported, the `>>` operator on
  //!     standard scalar types is the original one and so can not be overloaded on standard floating parameters
  //!     due to **C++** limitations.
  //!
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
  //! @godbolt{doc/arithmetic/shr.cpp}
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

}
#include <eve/module/arithmetic/regular/impl/shr.hpp>
