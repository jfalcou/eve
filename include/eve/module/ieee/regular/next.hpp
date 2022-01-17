//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/horizontal.hpp>
#include <eve/detail/overload.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/saturated.hpp>
#include <eve/concept/value.hpp>
#include <eve/assert.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var next
  //!
  //! @brief Callable object computing the next operation.
  //!
  //! **Required header:** `#include <eve/function/next.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the next operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, integral_value U > auto operator()( T x, U n = 1 ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `n`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!computes [elementwise](@ref glossary_elementwise), the `n`th  representable value greater than `x`.
  //!If `n` is zero returns `x`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::next
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `next[cond](x, ...)` is equivalent to `if_else(cond,next(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/next.hpp>`
  //!
  //!     The call `pedantic(next)(x)` distinguish `-0.0` and `+0.0` for floating point point inputs.
  //!      So `pedantic(next)(-0.0)` is `+0.0`.
  //!
  //!  * eve::saturated
  //!
  //!     **Required header:** `#include <eve/function/saturated/next.hpp>`
  //!
  //!     The call `pedantic(next)(x)` ensures for integral enties that `next(x, n) >= x`.
  //!     (equality is obtained only if `n == 0` or `x =  eve::valmax(as(x))`)
  //!
  //! #### Example
  //!
  //! @godbolt{doc/ieee/next.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct next_; }

  namespace detail
  {
    template<conditional_expr C, real_value T, integral_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::next_),  C const &
                              , T const& ,  [[ maybe_unused]] U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::next] : second parameter must be positive");
    }
    template<real_value T, integral_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::next_), T const& ,  [[ maybe_unused]] U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::next] : second parameter must be positive");
    }

    template<conditional_expr C, real_value T, integral_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::next_),  C const &
                              , T const&,  [[ maybe_unused]] U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::next] : second parameter must be positive");
    }
    template<real_value T, integral_value U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::next_), T const&,  [[ maybe_unused]]  U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[[eve::saturated([eve::next)] : second parameter must be positive");
    }
  }

  EVE_MAKE_CALLABLE(next_, next);
}

#include <eve/module/ieee/regular/impl/next.hpp>
