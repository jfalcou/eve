//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>
#include <eve/detail/kumi.hpp>

#include <iterator>
#include <type_traits>

namespace eve
{
  namespace detail
  {
    template<std::input_or_output_iterator T>
    constexpr auto value_type_impl()
    {
      return std::type_identity<typename std::iterator_traits<T>::value_type>{};
    }

    template <typename T>
    constexpr auto value_type_impl()
    {
      if constexpr ( requires { typename T::value_type; } )
      {
        return std::type_identity<typename T::value_type>{};
      }
      // Maybe this should be deleted
      else if constexpr ( kumi::product_type<T> )
      {
        auto mapper = []<typename U>(U)
        {
          return typename decltype( value_type_impl<U>() )::type{};
        };

        return std::type_identity<kumi::result::map_t<decltype(mapper), T>>{};
      }
    }

    template<range T>
    constexpr auto value_type_impl()
    {
      using ref = std::add_lvalue_reference_t<T>;
      return value_type_impl<decltype(std::begin(std::declval<ref>()))>();
    }

  }

  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!  @typedef value_type_t
  //!
  //!  @tparam T Type to process
  //!
  //!  @brief A meta function for getting an associated value_type for a relaxed iterator/range.
  //!
  //! value_type_t<T> is computed as follows:
  //!   - If T has begin/end - value_type_t for return type of begin
  //!   - If T is std::iterator -> returns iterator_traits<T>::value_type
  //!   - If T has nested `value_type` -> returns it
  //!   - If T is a product type and all elements have value_type_t defined for them -
  //!   -    kumi::tuple for the individual product types.
  //!   - Otherwise it's undefined.
  //!
  //! @tparam T Type to process
  //!
  //!  **Required header:** `#include <eve/traits.hpp>`
  //! @}
  //================================================================================================

  template <typename T>
    requires (!value<T> && !wide_cardinal<T>)
  using value_type_t = typename decltype(detail::value_type_impl<T>())::type;
}
