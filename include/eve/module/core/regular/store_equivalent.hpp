//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/memory.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup memory
//! @{
//!   @var store_equivalent
//!
//!   @brief Callable object, customisation point.
//!   If an iterator's store operation can be done as a store to some other
//!   iterator/pointer - this is a transformation to customize.
//!
//!   Should return new ignore/value/pointer triplep
//!
//!   By default returns ignore/value/pointer tuple, unchanged.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(store_equivalent_, store_equivalent);

//================================================================================================
//! @addtogroup memory
//! @{
//!   @var has_store_equivalent
//!
//!   @brief a concept, tests `store_equivalent` has a non-default definition for
//!          a value and a pointer.
//! @}
//================================================================================================
template<typename T, typename Ptr>
concept has_store_equivalent = simd_compatible_ptr<Ptr, T> &&(
    !std::same_as<kumi::tuple<ignore_none_, T, Ptr>,
                  decltype(store_equivalent(ignore_none, std::declval<T>(), std::declval<Ptr>()))>);
}

namespace eve::detail
{
template<relative_conditional_expr C, typename T, simd_compatible_ptr<T> Ptr>
EVE_FORCEINLINE kumi::tuple<C, T, Ptr>
                store_equivalent_(EVE_SUPPORTS(cpu_), C c, T v, Ptr ptr)
{
  return {c, v, ptr};
}
}
