//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <type_traits>
#include <cstdint>

namespace eve
{
  //================================================================================================
  //! @addtogroup utility
  //! @{
  //! @struct as_
  //! @brief Lightweight type-wrapper
  //!
  //! **Required header:** `#include <eve/as.hpp>`
  //!
  //! Wraps type into a constexpr, trivially constructible empty class to optimize passing type
  //! parameters via object instead of via template parameters
  //================================================================================================
  //! @}
  //================================================================================================
  template<typename T>
  struct as_
  {
    //! @brief Wrapped type
    using type = T;
  };

  //================================================================================================
  //! @brief Generates a type wrapper for the value type of `x`
  //! @relates eve::as_
  //! @param x  Object to wrap type from
  //! @return An instance of as_< std::decay_t<decltype(x)> >
  //================================================================================================
#if defined(EVE_DOXYGEN_INVOKED)
  template<typename T> EVE_FORCEINLINE constexpr as_<std::decay_t<T>> as(T&& x= {}) noexcept
#else
  template<typename T> EVE_FORCEINLINE constexpr as_<std::decay_t<T>> as(T&& = {}) noexcept
#endif
  {
    return {};
  }
}
