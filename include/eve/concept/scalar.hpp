//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/detail/meta.hpp>

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace eve::detail
{
// This is not directly a concept to prevent some compiler bugs about concepts depending
// on themselves. This should go away at one point in the future.
template<typename T>
constexpr bool is_plain() noexcept
{
  return    !(std::is_same_v<T, bool> || std::is_same_v<T, long double>)
        &&  (std::is_floating_point_v<T> || std::is_integral_v<T>);
}
}

namespace eve
{
template<typename Type> struct logical;

//==================================================================================================
//! @concept plain_scalar_value
//! @brief Specify that a type represents a plain scalar value
//!
//! The concept `plain_scalar_value<T>` is satisfied if and only if T is an instance of
//! any non-bool, non-long double, arithmetic types.
//!
//! ## Example Types
//! - `float`
//! - `int`
//==================================================================================================
template<typename T>
concept plain_scalar_value = detail::is_plain<T>();

//==================================================================================================
//! @concept logical_scalar_value
//! @brief Specify that a type represents a logical scalar value
//!
//! The concept `logical_scalar_value<T>` is satisfied if and only if T is an instance of
//! eve::logical and its contents satisfy eve::plain_scalar_value
//!
//! ## Example Types
//! - `logical<float>`
//! - `logical<int>`
//==================================================================================================
template<typename T>
concept logical_scalar_value = detail::instance_of<T, logical>
                               && plain_scalar_value<typename T::value_type>;
}

namespace eve::detail
{
template<typename T>
constexpr bool
scalar_tuple() noexcept
{
  if constexpr( !kumi::product_type<T> ) return false;
  else
  {
    constexpr auto f = []<typename M>(M)
    { return std::bool_constant<is_plain<M>() || logical_scalar_value<M>> {}; };

    using flt_t = kumi::result::flatten_all_t<kumi::as_tuple_t<T>, decltype(f)>;
    return kumi::all_of(flt_t {}, [](bool b) { return b; });
  }
}
}

namespace eve
{
//==================================================================================================
//! @concept product_scalar_value
//! @brief Specify that a type represents a product type made of scalars
//!
//! The concept `product_scalar_value<T>` is satisfied if and only if T is a kumi::product_type
//! containing only @ref eve::plain_scalar_value or @ref eve::logical_scalar_value
//! ## Example Types
//! - `kumi::tuple<float,int>`
//! - `kumi::tuple<logical<double>, char>`
//==================================================================================================
template<typename T>
concept product_scalar_value = detail::scalar_tuple<T>();

//==================================================================================================
//! @concept arithmetic_scalar_value
//! @brief Specify that a type represents a type suitable for vectorization
//!
//! The concept `arithmetic_scalar_value<T>` is satisfied if and only if T can be used as a base
//! type for @ref eve::wide , i.e it's either satisfying @ref eve::plain_scalar_value or
//! @ref eve::product_scalar_value
//!
//! ## Example Types
//! - `kumi::tuple<float,int>`
//! - `logical<double>`
//! - `float`
//==================================================================================================
template<typename T>
concept arithmetic_scalar_value = plain_scalar_value<T> || product_scalar_value<T>;
}
