//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup memory
//! @{
//! @var store
//!
//! @brief Callable object computing   //!  description NOT FOUND.
//!
//! **Required header:** `#include <eve/module/core.hpp>`
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
//!  template<value T, typename Dest>
//!  void operator()(T const& value, Dest* ptr) const noexcept
//!                                             requires( std::is_same_v<Dest, element_type_t<T>);
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//! **Parameters**
//!
//!  parameters NOT FOUND
//!
//! **Return value**
//!
//!  return values NOT FOUND
//!
//! ---
//!
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
//!  auto operator[]( conditional_expression auto cond ) const noexcept;
//!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!
//!  Higher-order function generating a masked version of eve::store
//!
//!  **Parameters**
//!
//!  `cond` : conditional expression
//!
//!  **Return value**
//!
//!  A Callable object so that the expression `store[cond](x, ...)` is equivalent to
//!  `if_else(cond,store(x, ...),x)`
//!
//! ---
//!
//! #### Supported decorators
//!
//!  no decorators are supported
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(store_, store);
}

#include <eve/module/core/regular/impl/store.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/store.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/store.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/store.hpp>
#endif
