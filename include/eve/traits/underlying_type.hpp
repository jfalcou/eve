//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/concept/scalar.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!
  //! @struct underlying_type
  //!
  //! @brief Computes the most scalar type associated with a type
  //!
  //! Retrieves the underlying type of one or more types, i.e the simplest type on which
  //! constraints and concept can be applied to.
  //!
  //! By definition:
  //!   - the underlying type of any @ref eve::plain_scalar_value is the type itself
  //!   - the underlying type of any @ref eve::logical_scalar_value is the type itself,
  //!   - the underlying type of any @ref eve::simd_value is the underlying type of its value type.
  //!
  //! For user-defined type, one can either specialize @ref eve::underlying_type or provide an
  //! internal typedef named `underlying_type` that will be picked up instead.
  //!
  //! **Required header:** `#include <eve/traits/underlying_type.hpp>`
  //!
  //! @tparam T Type to inspect
  //!
  //! #### Helper type
  //!
  //! @code{.cpp}
  //! template<typename... Ts>
  //! using underlying_type_t = typename underlying_type<Ts...>::type;
  //! @endcode
  //!
  //! @}
  //================================================================================================
  template<typename Ts>
  struct underlying_type;

  template<typename T>
  requires requires { typename T::underlying_type; }
  struct underlying_type<T>
  {
    using type = typename T::underlying_type;
  };

  template<plain_scalar_value T>
  struct underlying_type<T>
  {
    using type = T;
  };

  template<>
  struct underlying_type<bool>
  {
    using type = bool;
  };

  template<typename T>
  struct underlying_type<logical<T>>
  {
    using type = logical<typename underlying_type<T>::type>;
  };

  template<typename T, typename N>
  struct underlying_type<wide<T,N>> : underlying_type<T>
  {};

  template<typename Ts>
  using underlying_type_t = typename underlying_type<Ts>::type;
}
