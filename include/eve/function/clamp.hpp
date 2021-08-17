//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/all.hpp>
#include <eve/assert.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var clamp
  //!
  //! @brief Callable object clamping a value between two others.
  //!
  //! **Required header:** `#include <eve/function/clamp.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the clamping operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T, real_value U, real_value V > auto operator()( T x, U lo, V hi ) const noexcept
  //!  requires compatible< T, U > && compatible< T, V >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:    [value](@ref eve::value) to clamp.
  //!
  //!`lo`, `hi`:    the boundary [values](@ref eve::value) to clamp `x` to.
  //!
  //! **Return value**
  //!
  //!Each [element](@ref glossary_element)  of the result contains:
  //!   -  `lo`, if `x` is less than `lo`.
  //!   -  `hi`, if `hi` is less than `x`.
  //!   -  otherwise `x`.
  //!
  //!The result type is the [common compatible type](@ref common_compatible) of the three parameters.
  //!
  //!@warning
  //!    Contrary to the standard implementation `clamp` does not return a reference.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::clamp
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `clamp[cond](x, ...)` is equivalent to `if_else(cond,clamp(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_3rd, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/clamp.hpp>`
  //!
  //!     The expression `diff_1st(clamp)(x,y,z)`, `diff_2nd(clam)(x,y,z)` and `diff_3rd(clam)(x,y,z)` computes the partial
  //!      derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y,z) \rightarrow \ \mbox{clamp}(x,y,z)\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/clamp.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct clamp_; }

  namespace detail
  {
    template<typename X, typename L, typename H>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::clamp_)
                              , X const&
                              , [[maybe_unused]] L const& lo
                              , [[maybe_unused]] H const& hi)
    {
      EVE_ASSERT(eve::all(lo <= hi), "[eve::clamp] Unordered clamp boundaries");
    }
  }
  EVE_MAKE_CALLABLE(clamp_, clamp);

}

#include <eve/module/real/core/function/regular/generic/clamp.hpp>
