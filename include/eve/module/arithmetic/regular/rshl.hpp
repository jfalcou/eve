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
#include <eve/function/abs.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup operators
  //! @{
  //! @var rshl
  //!
  //! @brief Callable object computing the arithmetic left/right shift operation according to shift sign.
  //!
  //! **Required header:** `#include <eve/function/rshl.hpp>`
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
  //!`x`:   [value](@ref eve::value).
  //!
  //!`n`:   [integral value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes the [elementwise](@ref glossary_elementwise) arithmetic left/right shift of the first parameter by the second one.
  //!
  //!the call `rshl(x, n)` is equivalent to `if_else(n>0, shl(x, n), shr(x, n))` if `x`  is an  [simd value](@ref eve::simd_value).
  //!
  //!The types must share the same cardinal or be scalar and if `N` is the size in bits  of the element type of `T`,
  //!all  [elements](@ref glossary_elementwise) of n must belong to the
  //!interval: `]-N, N[` or the result is undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::rshl
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `rshl[cond](x, ...)` is equivalent to `if_else(cond,rshl(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/rshl.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct rshl_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::rshl_), T const&, [[ maybe_unused ]]S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(eve::abs(s)),
                  "[eve::rshl] - Shifting by " << s
                  << " is out of the range ]"
                  << -int(sizeof(value_type_t<T>) * 8)
                  << ", "
                  << sizeof(value_type_t<T>) * 8
                  << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(rshl_, rshl);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/rshl.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/rshl.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/rshl.hpp>
#endif
