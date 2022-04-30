//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <type_traits>

//==================================================================================================
//! @addtogroup traits
//! @{
//!   @defgroup struct Structured Types Management
//!   @brief Traits and functions to handle user defined types in SIMD registers
//!
//!   **EVE** provides various elements to simplify the management of user-defined structures
//!   as vectorized types.
//!
//!   **Convenience header:** @code{.cpp} #include <eve/product_type.hpp> @endcode
//! @}
//==================================================================================================

namespace eve
{
  //================================================================================================
  // Reinject kumi concept & traits in EVE
  using kumi::product_type;
  using kumi::sized_product_type;
  using kumi::is_product_type;

  //================================================================================================
  //! @addtogroup struct
  //! @{
  //================================================================================================

  //================================================================================================
  //! @brief  Register a user-defined type to supports ordering
  //!
  //! @tparam Type  Type to register as supporting ordering operators
  //!
  //! **Required header:** `#include <eve/product_type.hpp>`
  //!
  //! By default, instances of `eve::wide<T>` where `T` is an User-Defined Product Type supports
  //! ordering. However, one can specialize `eve::supports_ordering` for a given type to evaluates
  //! to `false` in order to disable ordering for this type.
  //!
  //! Alternatively, any type `T` providing an internal `eve_disable_ordering` type will be
  //! treated as if `eve::supports_ordering<T>::``value` evaluates to `false`, thus disabling
  //! ordering operators for `eve::wide<T>`.
  //!
  //! ### Helper variable template
  //!
  //! @code
  //! template<typename Type>
  //! inline constexpr bool supports_ordering_v = eve::supports_ordering<Type>::value;
  //! @endcode
  //================================================================================================
  template<typename Type> struct supports_ordering : std::true_type
  {};

  template<typename Type>
  requires requires(Type t) { typename Type::eve_disable_ordering; }
  struct supports_ordering<Type> : std::false_type
  {};

  template<typename Type>
  inline constexpr bool supports_ordering_v = supports_ordering<Type>::value;

  //================================================================================================
  //! @brief Opt-in traits for eve::like concept compliance
  //!
  //! **Required header:** `#include <eve/product_type.hpp>`
  //!
  //! `eve::supports_like` is meant ot be specialized to indicates that `Wrapper` models
  //! `eve::like<Wrapper,T>`.
  //!
  //! @tparam Wrapper Type to adapt for the eve::like concept
  //! @tparam Self    Type to
  //================================================================================================
  template<typename Wrapper, typename Self> struct supports_like : std::false_type {};

  template <typename Wrapper, typename Self>
  requires requires(Wrapper) { typename Wrapper::is_like; }
  struct supports_like<Wrapper, Self> :
  std::bool_constant<std::same_as<Self, typename std::remove_cvref_t<Wrapper>::is_like>>
  {};

  //================================================================================================
  //! @brief Specifies semantic compatibility between wrapper/wrapped types
  //!
  //! **Required header:** `#include <eve/product_type.hpp>`
  //!
  //! `eve::like<Wrapper, T>` is a concept that indicates that a wrapper type provides most of the
  //! functionality of another type `T`. By definition `T` always models `eve::like<T>`.
  //!
  //! A `Wrapper` models `like< Wrapper, T>` if it either defines an internal type `is_like` that
  //! evaluates to `T` or `eve::supports_like<Wrapper,T>` is specialized to evaluates to `T`.
  //!
  //! @groupheader{Examples}
  //!  - `eve::wide<T>` models `eve::like<eve::wide<T>,T>`
  //================================================================================================
  template<typename Wrapper, typename Self>
  concept like = std::same_as<std::remove_cvref_t<Wrapper>, Self> ||
                 supports_like<std::remove_cvref_t<Wrapper>, Self>::value;

  //================================================================================================
  //! @brief CRTP base-class to declare operators for user-defined product type
  //!
  //! **Required header:** `#include <eve/product_type.hpp>`
  //!
  //! `eve::struct_support` is a CRTP based helper class to define product type like user-defined
  //! type. If `Self`this type that inherits from `eve::struct_supports<Self,Fields...>`, it will
  //! behave as a structure containing members of type `Fields...` and provides supports for
  //! operators based on the implementation of `Self`.
  //!
  //! Generated operators include:
  //!   - Member-wise equality is provided by default
  //!   - Lexicographial order is provided unless `eve::supports_ordering<Self>::value` evaluates to `false`
  //!   - Binary operators are provided if the corresponding compound assignment operator is provided.
  //!     E.g `operator+` will be generated if `Self::operator+=` is defined. Note that no operators
  //!     is generated by combining existing operator (like operator-= b from operator+= and operator-)
  //!     to maximize optimization opportunities.
  //!
  //! `eve::struct_support` also automatically generates the data member for `Self` that are
  //!  stored within a `kumi::tuple` and accessible via `get<N>(*this)`.
  //!
  //! @tparam Self    Type to use as CRTP derived class
  //! @tparam Fields  Variadic list describing the data member of `Self`
  //!
  //! @groupheader{Examples}
  //!
  //! @godbolt{doc/traits/struct_support.cpp}
  //================================================================================================
  template <typename Self, typename... Fields>
  struct struct_support;

  namespace detail
  {
    std::false_type derived_from_struct_support_impl(...);

    template <typename Self, typename ... Fields>
    std::true_type derived_from_struct_support_impl(struct_support<Self, Fields...> const&);

    template <typename Type>
    concept derived_from_struct_support = decltype(derived_from_struct_support_impl(Type{}))::value;
  }

  template <typename Self, typename ... Fields>
  struct struct_support : kumi::tuple<Fields...>
  {
    using tuple_type = kumi::tuple<Fields...>;

    template<like<Self> Z1, like<Self> Z2>
    EVE_FORCEINLINE friend auto operator+(Z1 x, Z2 y) requires requires { x += x; }
    {
      if constexpr(scalar_value<Z1> && simd_value<Z2>)
      {
        as_wide_t<Z1> that{x};
        return that += y;
      }
      else
      {
        x += y;
        return x;
      }
    }

    EVE_FORCEINLINE friend auto operator-(eve::like<Self> auto x, eve::like<Self> auto y) requires requires { x -= y; }
    {
      x -= y;
      return x;
    }

    EVE_FORCEINLINE friend auto operator*(eve::like<Self> auto x, eve::like<Self> auto y) requires requires { x *= y; }
    {
      x *= y;
      return x;
    }

    EVE_FORCEINLINE friend auto operator/(eve::like<Self> auto x, eve::like<Self> auto y) requires requires { x /= y; }
    {
      x /= y;
      return x;
    }

    EVE_FORCEINLINE friend auto operator%(eve::like<Self> auto x, eve::like<Self> auto y) requires requires { x %= y; }
    {
      x %= y;
      return x;
    }

    EVE_FORCEINLINE friend auto operator^(eve::like<Self> auto x, eve::like<Self> auto y) requires requires { x ^= y; }
    {
      x ^= y;
      return x;
    }

    EVE_FORCEINLINE friend auto operator&(eve::like<Self> auto x, eve::like<Self> auto y) requires requires { x &= y; }
    {
      x &= y;
      return x;
    }

    EVE_FORCEINLINE friend auto operator|(eve::like<Self> auto x, eve::like<Self> auto y) requires requires { x |= y; }
    {
      x |= y;
      return x;
    }

    EVE_FORCEINLINE friend auto operator<<(eve::like<Self> auto x, integral_value auto s) requires requires { x <<= s; }
    {
      x <<= s;
      return x;
    }

    EVE_FORCEINLINE friend auto operator>>(eve::like<Self> auto x, integral_value auto s) requires requires { x >>= s; }
    {
      x >>= s;
      return x;
    }

    friend auto operator< (eve::like<Self> auto x, eve::like<Self> auto y) requires (!supports_ordering_v<Self>) = delete;
    friend auto operator<=(eve::like<Self> auto x, eve::like<Self> auto y) requires (!supports_ordering_v<Self>) = delete;
    friend auto operator> (eve::like<Self> auto x, eve::like<Self> auto y) requires (!supports_ordering_v<Self>) = delete;
    friend auto operator>=(eve::like<Self> auto x, eve::like<Self> auto y) requires (!supports_ordering_v<Self>) = delete;
  };
  //================================================================================================
  //! @}
  //================================================================================================
}

template <eve::detail::derived_from_struct_support Type>
struct std::tuple_size<Type> : std::tuple_size<typename Type::tuple_type> {};

template <std::size_t I, eve::detail::derived_from_struct_support Type>
struct std::tuple_element<I, Type> : std::tuple_element<I, typename Type::tuple_type> {};
