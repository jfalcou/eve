//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/translation.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/detail/ptr.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/traits/value_type.hpp>

#include <bit>
#include <new>

namespace eve
{
  //================================================================================================
  //! @brief Translates a value to its translated type.
  //!
  //! @param val The value to translate
  //! @return The translated value of type `translate_t<V>`
  //================================================================================================
  template <typename V>
  constexpr translate_t<V> translate(V const& val)
  {
    if constexpr (has_plain_translation<element_type_t<V>>) return std::bit_cast<translate_t<V>>(val);
    else                                                    return val;
  }

  //================================================================================================
  //! @brief Translates an `std::array` to an `std::array` of its translated value type and the same size.
  //!
  //! @param T The element type of the array to translate
  //! @param N The size of the array to translate
  //! @return The translated array of type `std::array<translate_t<V>, N>`
  //================================================================================================
  template <typename T, size_t N>
  constexpr std::array<translate_t<T>, N> translate(std::array<T, N> val)
  {
    if constexpr (has_plain_translation<element_type_t<T>>) return std::bit_cast<std::array<translate_t<T>, N>>(val);
    else                                                    return val;
  }

  //================================================================================================
  //! @brief Translates a mutable reference to a reference its translated type.
  //!
  //! @param val The mutable reference to translate
  //! @return A mutable reference to the translated representation of `val`
  //================================================================================================
  template <typename V>
  constexpr translate_t<V>& translate(V& val)
  {
    return reinterpret_cast<translate_t<V>&>(val);
  }

  //================================================================================================
  //! @brief Translates an `as` type wrapper to a type wrapper of its translated type.
  //!
  //! @tparam V The wrapper type to translate
  //! @return Type tag for the translated type
  //!
  //! @example
  //! @code
  //!   enum class E: int { };
  //!   eve::as<E> tag;
  //!   static_assert(std::same_as<decltype(eve::translate(tag)), eve::as<int>>);
  //! @endcode
  //================================================================================================
  template <typename V>
  constexpr auto translate(as<V>)
  {
    return as<translate_t<V>>{};
  }

  //================================================================================================
  //! @brief Translates a pointer to get a pointer to the same value through its translated type.
  //!
  //! @param ptr The pointer to translate
  //! @return A pointer of the translated type
  //!
  //! @example
  //! @code
  //!   enum class E: int { };
  //!   E* ptr;
  //!   static_assert(std::same_as<decltype(eve::translate_ptr(ptr)), int*>);
  //! @endcode
  //================================================================================================
  template <detail::scalar_pointer Ptr>
  constexpr auto translate_ptr(Ptr ptr)
  {
    if constexpr (has_plain_translation<value_type_t<Ptr>>)
    {
      using trans_t = detail::copy_qualifiers_t<translated_value_type_t<Ptr>, Ptr>;

      if constexpr (std::is_pointer_v<Ptr>)
      {
        return std::launder(reinterpret_cast<trans_t*>(ptr));
      }
      else
      {
        return std::bit_cast<typename Ptr::template rebind<trans_t>>(ptr);
      }
    }
    else
    {
      return ptr;
    }
  }

  //================================================================================================
  //! @brief Performs a translation between two types that are part of the same translation tree.
  //!
  //! @param val The source value to translate
  //! @tparam Dst The destination type to translate into
  //!
  //! @example
  //! @code
  //!   enum class A : int { };
  //!   enum class B : int { };
  //!   A a;
  //!   B b = eve::translate_into(a, eve::as<B>{});
  //! @endcode
  //================================================================================================
  template <typename Dst, translatable_into<Dst> Src>
  constexpr Dst translate_into(Src const& val, as<Dst>)
  {
    return std::bit_cast<Dst>(val);
  }
}
