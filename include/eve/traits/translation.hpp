//==================================================================================================
/*
    EVE - Expressive Vector Engine
    Copyright : EVE Project Contributors
    SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <type_traits>
namespace eve
{
  //! @brief Indicates to EVE that a type is translateable and its translation target.
  //!
  //! By default, most EVE functions only work on fundamental types.
  //! Translation allows the user to specify that a custom type should be treated as one of the fundamental types when
  //! used in EVE.
  //!
  //! @tparam T The type to be translated
  //!
  //! Example:
  //! @code
  //! // Custom type that should be treated as an int
  //! struct MyInt { int value; };
  //!
  //! // Specialize translation_of to map MyInt to int in EVE
  //! template<>
  //! struct eve::translation_of<MyInt> { using type = int; };
  //! @endcode
  //!
  //! @note A translatable type's translation target can be a translateable type itself. In this case, EVE will
  //!       recursively resolve the translation until it reaches a fundamental type.
  template <typename T>
  struct translation_of
  {
    using type = T;
  };

  //! @brief Defines the requirements for a struct to be translatable.
  //!
  //! @tparam T The translation candidate type
  //!
  //! `T` must satisfies this concept in order to be safely used as a translateable type.
  //! `T` must be trivially consstructible, copyable, and assignable to guarantee that scalar operations produce
  //! the same results as vectorized operations executed on values of `T` when viewed as their translation targets.
  //! `T`and its translation target must have the same size and alignment to reduce the risks of undefined behavior when
  //! translating between them.
  template <typename T>
  concept translatable_struct = std::is_trivially_copyable_v<T>
                              && std::is_trivially_assignable_v<T&, T>
                              && std::is_trivially_default_constructible_v<T>
                              && std::is_trivially_constructible_v<T, typename translation_of<T>::type>
                              && (sizeof(T) == sizeof(typename translation_of<T>::type))
                              && (alignof(T) == alignof(typename translation_of<T>::type));

  //! @brief Determines if a type can be translated.
  //!
  //! @note This also convers non-translatable types as their translation target is themselves by default.
  template <typename T>
  concept translatable = std::same_as<typename translation_of<T>::type, T>
                      || std::is_enum_v<T>
                      || translatable_struct<T>;

  namespace detail
  {
    template <typename T>
    consteval auto as_translated_type(as<T>)
    {
      if constexpr (requires { typename T::translated_type; })
      {
        return as<typename T::translated_type>{};
      }
      else if constexpr (std::is_same_v<typename translation_of<T>::type, T>)
      {
        return as<T>{};
      }
      else if constexpr (std::is_enum_v<T>)
      {
        return as<typename translation_of<T>::type>{};
      }
      else
      {
        return as_translated_type(as<typename translation_of<T>::type>{});
      }
    }
  }

  //! @brief Returns the final translated type of `T`.
  //!
  //! Recursively translates the type `T` until `translation_of<T>` is `T`.
  template <translatable T>
  using translate_t = typename decltype(detail::as_translated_type(as<T>{}))::type;

  // All enums are translateable into their underlying type by default.
  template <typename T>
  requires (std::is_enum_v<T>)
  struct translation_of<T>: std::underlying_type<T>
  { };
}
