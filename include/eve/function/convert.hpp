//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup conversion
  //! @{
  //! @var convert
  //!
  //! @brief Callable object computing   //!  description NOT FOUND.
  //!
  //! **Required header:** `#include <eve/function/convert.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` |   //!  description NOT FOUND   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<value T, scalar_value Target>
  //!  auto operator()( T const& x, as_<Target> const& t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value) to convert.
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type to convert `x` to.
  //!
  //! **Return value**
  //!
  //!For a [value](@ref eve::value) `x` and any type `Target` the expression:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!auto r = convert(x, as_<Target>{});
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically equivalent to:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!Target r;
  //!
  //!if constexpr( scalar_value<T> )
  //!{
  //!  r = static_cast<Target>(x);
  //!}
  //!else if constexpr( simd_value<T> )
  //!{
  //!  for(std::size_t i=;i<x.size();++i)
  //!    r[i] = static_cast<Target>(x[i]);
  //!}
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!@warning Note
  //!   Conversion operated by [eve::convert](#eve::convert) follows the regular rules of C++ type conversion, including the cases leading to Undefined Behaviors.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::convert
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `convert[cond](x, ...)` is equivalent to `if_else(cond,convert(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::saturated
  //!
  //!     **Required header:** `#include <eve/function/saturated/convert.hpp>`
  //!
  //!     The expression `saturated(convert)(x,t)` computes a saturated conversion of `x` to the type wrapped by `t`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/convert.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(convert_, convert);
}

#include <eve/module/real/core/function/regular/generic/convert.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/convert.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/convert.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/convert.hpp>
#endif
