//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/callable.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup operators
  //! @{
  //! @var shl
  //!
  //! @brief Callable object computing the arithmetic left shift operation.
  //!
  //! **Required header:** `#include <eve/function/shl.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the arithmetic left shift operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, integral_real_value U > auto operator()( T x, U n ) const noexcept
  //!   requires bit_compatible< T, U >;
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
  //!Computes the [elementwise](@ref glossary_elementwise) arithmetic left shift of the first parameter by the second one.
  //!
  //!the call `shl(x, n)` is equivalent to `x << n` if `x`  is an  [simd value](@ref eve::simd_value).
  //!
  //!The types must share the same cardinal or be scalar and if `N` is the size in bits  of the element type of `T`,
  //!all  [elements](@ref glossary_elementwise) of n must belong to the
  //!interval: `[0, N[` or the result is undefined.
  //!
  //!  @warning
  //!     Although the infix notation with `<<` is supported, the `<<` operator on
  //!     standard scalar types is the original one and so can not be overloaded on standard floating parameters
  //!     due to **C++** limitations.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::shl
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `shl[cond](x, ...)` is equivalent to `if_else(cond,shl(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/shl.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct shl_ {}; }

  namespace detail
  {
    struct callable_shl_  : callable<tag::shl_,callable_shl_>
    {
      template<typename T, typename U>
      static EVE_FORCEINLINE void check(T const&, [[maybe_unused]] U const& s)
      {
        EVE_ASSERT( assert_good_shift<T>(s),
                    "[eve::shl] Shifting by " << s
                                              << " is out of the range [0, "
                                              << sizeof(value_type_t<T>) * 8
                                              << "[."
                  );
      }

      // Proceed to the actual computation
      template<typename T, typename S>
      static EVE_FORCEINLINE constexpr auto evaluate(T a, S s) noexcept
      {
              if constexpr(scalar_value<T> && scalar_value<S>) return static_cast<T>(a << s);
        else  if constexpr(scalar_value<T>)               return as_wide_t<T, cardinal_t<S>>(a) << s;
        else                                              return a << s;
      }

      template<typename C, typename T, typename S>
      static EVE_FORCEINLINE constexpr auto evaluate(C const& c, T a, S s) noexcept
      {
        return mask_op(c, callable_shl_{}, a, s);
      }

      // Provide the concept-based interface
      template<value T, integral_real_value S>
      EVE_FORCEINLINE constexpr auto operator()(T a, S s) const noexcept
      {
        check(a,s);
        return callable<tag::shl_, callable_shl_>::dispatch(a,s);
      }
    };
  }

  EVE_BUILD_CALLABLE(shl_, shl);
}
