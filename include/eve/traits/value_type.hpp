//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
    template <typename T>
    constexpr auto value_type_impl()
    {
      if constexpr (range<T>)
      {
        using ref = std::add_lvalue_reference_t<T>;
        return value_type_impl<decltype(std::begin(std::declval<ref>()))>();
      }
      else if constexpr (std::input_or_output_iterator<T>)
      {
        return std::type_identity<typename std::iterator_traits<T>::value_type>{};
      }
      else if constexpr ( requires { typename T::value_type; } )
      {
        return std::type_identity<typename T::value_type>{};
      }
      // Maybe this should be deleted
      else if constexpr ( kumi::product_type<T> )
      {
        auto mapper = []<typename U>(U) {
          return typename decltype( value_type_impl<U>() )::type{};
        };

        return std::type_identity<kumi::result::map_t<decltype(mapper), T>>{};
      }
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
  //!         If T has begin/end - value_type_t for return type of begin
  //!         If T is std::iterator -> returns iterator_traits<T>::value_type
  //!         If T has nested `value_type` -> returns it
  //!         If T is a product type and all elements have value_type_t defined for them -
  //!            kumi::tuple for the individual product types.
  //!         Otherwise it's undefined.
  //!
  //!   **Required header:** `#include <eve/traits/value_type.hpp>`,
  //!                        `#include <eve/traits.hpp>`
  //! @}
  //================================================================================================

  template <typename T>
    requires (!value<T>)
  using value_type_t = typename decltype(detail::value_type_impl<T>())::type;
}
