//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/arch/abi_of.hpp>
#include <eve/forward.hpp>

#include <concepts>
#include <type_traits>

namespace eve::detail
{
  // Types that are too big and are not emulated require aggregation
  template<typename Type, typename Size>
  inline constexpr bool require_aggregation =     (Size::value > expected_cardinal_v<Type>)
                                              && !std::is_same_v
                                                        < abi_of_t< Type
                                                                  , expected_cardinal_v<Type>
                                                                  >
                                                        , eve::emulated_
                                                        >;
}

namespace eve
{
  template<typename T> concept arithmetic = std::is_arithmetic_v<T>;

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!
  //! @struct abi
  //! @brief Find proper ABI for Type/Lanes pair
  //!
  //! Computes the best ABI to use to efficiently store `Lanes` elements of type `Type` in
  //! order to use SIMD implementations.
  //!
  //! @tparam Type  Type of the element to store
  //! @tparam Lanes Number of elements to store
  //!
  //! #### Member types
  //!
  //! |Name   | Definition                                                  |
  //! |:------|:------------------------------------------------------------|
  //! |`type` | The tag for the ABI to use for current Type/lanes selection |
  //!
  //! <br/>
  //! #### Helper types
  //!
  //! @code{.cpp}
  //! template<typename Type, typename Lanes>
  //! using abi_t = typename abi<Type,Lanes>::type;
  //! @endcode
  //!
  //! @}
  //================================================================================================
  template<typename Type, typename Lanes> struct abi {};

#if !defined(EVE_DOXYGEN_INVOKED)
  template<typename Type, typename Lanes>
  requires( arithmetic<Type> && detail::require_aggregation<Type, Lanes> )
  struct abi<Type, Lanes>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, typename Lanes>
  requires( kumi::product_type<Type> )
  struct abi<Type, Lanes>
  {
    using type = eve::bundle_;
  };

  template<typename Type, typename Lanes>
  requires( arithmetic<Type> && !detail::require_aggregation<Type, Lanes> )
  struct abi<Type, Lanes> : abi_of<Type, Lanes::value>
  {};

  // Wrapper for SIMD registers holding logical type
  template<typename Type, typename Lanes>
  requires( arithmetic<Type> && detail::require_aggregation<Type, Lanes> )
  struct abi<logical<Type>, Lanes>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, typename Lanes>
  requires( arithmetic<Type> && !detail::require_aggregation<Type, Lanes> )
  struct abi<logical<Type>, Lanes> : abi_of<logical<Type>, Lanes::value>
  {};
#endif

  // Type short-cut
  template<typename Type, typename Lanes>
  using abi_t = typename abi<Type, Lanes>::type;
}
