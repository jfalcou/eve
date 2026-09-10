//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/expected_width.hpp>
#include <eve/arch/float16.hpp>
#include <eve/deps/kumi.hpp>
#include <eve/arch/abi_of.hpp>

#include <concepts>
#include <type_traits>

namespace eve::_
{
  // Types that are too big and are not emulated require aggregation
  template<typename Type, width_type Width>
  inline constexpr bool require_aggregation = (Width > expected_width_v<Type>)
                                              && !std::is_same_v
                                                        < abi_of_t< Type
                                                                  , expected_width_v<Type>
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
  //! @addtogroup eve_traits
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
  //! template<typename Type, width_type Size>
  //! using abi_t = typename abi<Type, Size>::type;
  //! @endcode
  //!
  //! @}
  //================================================================================================
  template<typename Type, width_type Width> struct abi {};

#if !defined(EVE_DOXYGEN_INVOKED)
  template<typename Type, width_type Width>
  requires( arithmetic<Type> && _::require_aggregation<Type, Width> )
  struct abi<Type, Width>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, width_type Width>
  requires( eve::product_type<Type> )
  struct abi<Type, Width>
  {
    using type = eve::bundle_;
  };

  template<typename Type, width_type Width>
  requires( arithmetic<Type> && !_::require_aggregation<Type, Width> )
  struct abi<Type, Width> : abi_of<Type, Width>
  {};

  // Wrapper for SIMD registers holding logical type
  template<typename Type, width_type Width>
  requires( arithmetic<Type> && _::require_aggregation<Type, Width> )
  struct abi<logical<Type>, Width>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, width_type Width>
  requires( arithmetic<Type> && !_::require_aggregation<Type, Width> )
  struct abi<logical<Type>, Width> : abi_of<logical<Type>, Width>
  {};
#endif

  // Type short-cut
  template<typename Type, width_type Width>
  using abi_t = typename abi<translate_t<Type>, Width>::type;
}
