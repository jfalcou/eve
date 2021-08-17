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

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var bit_shr
  //!
  //! @brief Callable object computing the logical right shift operation.
  //!
  //! **Required header:** `#include <eve/function/bit_shr.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical right shift operation                          |
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
  //!Computes the [elementwise](@ref glossary_elementwise) logical right shift of the first parameter by the second one.
  //!
  //!the call `bit_shr(x, n)` is equivalent to `x >> n` if `x`  is an  [simd value](@ref eve::simd_value).
  //!
  //!The types must share the same cardinal or be scalar and if \f$N\f$ is the size in bits  of the element type of `T`,
  //!all  [elements](@ref glossary_element) of n must belong to the
  //!interval: \f$[0, N[\f$ or the result is undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::bit_shr
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bit_shr[cond](x, ...)` is equivalent to `if_else(cond,bit_shr(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/bit_shr.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct bit_shr_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::bit_shr_), T const&,  [[maybe_unused]] S const& s)
    {
      EVE_ASSERT( assert_good_shift<T>(s),
                  "[eve::bit_shr] Shifting by " << s
                                                << " is out of the range [0, "
                                                << sizeof(value_type_t<T>) * 8
                                                << "[."
                );
    }
  }

  EVE_MAKE_CALLABLE(bit_shr_, bit_shr);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/bit_shr.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/bit_shr.hpp>
#endif
