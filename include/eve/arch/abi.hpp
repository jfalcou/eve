//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/float16.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/arch/abi_of.hpp>

#include <concepts>
#include <type_traits>

namespace eve::_
{
  // Types that are too big and are not emulated require aggregation
  template<typename Type, size Size>
  inline constexpr bool require_aggregation = (Size > expected_cardinal_v<Type>)
                                              && !std::is_same_v
                                                        < abi_of_t< Type
                                                                  , expected_cardinal_v<Type>
                                                                  >
                                                        , eve::emulated_
                                                        >;
}

namespace eve
{
  namespace
  {
    template<typename T> concept arithmetic = std::is_arithmetic_v<T> || std::same_as<T, eve::float16_t>;
  }

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!
  //! @struct abi
  //! @brief Find proper ABI for Type/Size pair
  //!
  //! Computes the best ABI to use to efficiently store `Size` elements of type `Type` in
  //! order to use SIMD implementations.
  //!
  //! @tparam Type Type of the element to store
  //! @tparam Size Number of elements to store
  //!
  //! #### Member types
  //!
  //! |Name   | Definition                                                  |
  //! |:------|:------------------------------------------------------------|
  //! |`type` | The tag for the ABI to use for current Type/Size selection |
  //!
  //! <br/>
  //! #### Helper types
  //!
  //! @code{.cpp}
  //! template<typename Type, size Size>
  //! using abi_t = typename abi<Type, Size>::type;
  //! @endcode
  //!
  //! @}
  //================================================================================================
  template<typename Type, size Size> struct abi {};

#if !defined(EVE_DOXYGEN_INVOKED)
  template<typename Type, size Size>
  requires( arithmetic<Type> && _::require_aggregation<Type, Size> )
  struct abi<Type, Size>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, size Size>
  requires( eve::product_type<Type> )
  struct abi<Type, Size>
  {
    using type = eve::bundle_;
  };

  template<typename Type, size Size>
  requires( arithmetic<Type> && !_::require_aggregation<Type, Size> )
  struct abi<Type, Size> : abi_of<Type, Size>
  {};

  // Wrapper for SIMD registers holding logical type
  template<typename Type, size Size>
  requires( arithmetic<Type> && _::require_aggregation<Type, Size> )
  struct abi<logical<Type>, Size>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, size Size>
  requires( arithmetic<Type> && !_::require_aggregation<Type, Size> )
  struct abi<logical<Type>, Size> : abi_of<logical<Type>, Size>
  {};
#endif

  // Type short-cut
  template<typename Type, size Size>
  using abi_t = typename abi<translate_t<Type>, Size>::type;
}
