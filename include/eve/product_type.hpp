//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/concept/vectorized.hpp>

//==================================================================================================
//! @addtogroup utility
//! @{
//! @defgroup struct Structured Types Management
//!
//! **EVE** provides various elements to simplify the management of user-defined structures
//! as vectorized types.
//!
//! **Convenience header:** @code{.cpp} #include <eve/product_type.hpp> @endcode
//!
//! @}
//==================================================================================================

namespace eve
{
  // Reinject kumi concept in EVE
  using kumi::product_type;

  //================================================================================================
  //! @addtogroup struct
  //! @{
  //================================================================================================
  //==============================================================================================
  //! @brief Extract the Ith element of a eve::product_type instance.
  //!
  //! The values of `idx` must be integer between 0 and `size()-1` or equal to eve::na_ to
  //! indicate the value at this lane must be replaced by zero.
  //!
  //! Does not participate in overload resolution if `I` is greater than the number of members of
  //! `t`.
  //!
  //! @param  t  value to extract a member from
  //! @tparam I  Index of the member to extract
  //!
  //! @return The Ith element of the product type value passed as parameter
  //==============================================================================================
  template<std::size_t I, typename T>
  constexpr decltype(auto) content(T&& t) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
  requires( I < std::tuple_size<eve::element_type_t<std::remove_cvref_t<T>>>::value )
#endif
  {
    if constexpr( simd_value<std::remove_cvref_t<T>> )  return get<I>(std::forward<T>(t).storage());
    else                                                return get<I>(std::forward<T>(t));
  }

  //==============================================================================================
  //! @brief Extension point for product type operator support
  //!
  //! @tparam Type  eve::product_type to adapt
  //! @tparam Tag   List of all operators tags to add to `Type`
  //==============================================================================================
  template<typename Type,typename... Tag>
  struct supports : supports<Type,Tag>...
  {};

  //================================================================================================
  //! @}
  //================================================================================================
}
