//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/is_flint.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup ieee754
  //! @{
  //! @var ldexp
  //!
  //! @brief Callable object computing the ldexp operation: \f$\textstyle x 2^n\f$.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ldexp operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, integral_real_value U > auto operator()( T x, U n ) const noexcept
  //!  requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //!`n`:   [integral real value](@ref eve::integral_value).
  //!
  //! **Return value**
  //!
  //!the call `ldexp(x,n)` is semantically equivalent to  \f$\textstyle x 2^n\f$:
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::ldexp
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ldexp[cond](x, n)` is equivalent to `if_else(cond,ldexp(x, n),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/ldexp.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct ldexp_; }

  namespace detail
  {
    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_SUPPORTS(eve::tag::ldexp_), T const&, [[maybe_unused]]  U const& b)
    {
      if constexpr(std::is_floating_point_v<element_type_t<U>>)
        EVE_ASSERT(eve::all(is_flint(b)), "[eve::ldexp] argument 2 is floating but not a flint");
    }
  }

  EVE_MAKE_CALLABLE(ldexp_, ldexp);
}

#include <eve/module/core/regular/impl/ldexp.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/ldexp.hpp>
#endif
