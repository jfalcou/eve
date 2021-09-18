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
#include <type_traits>

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
  //================================================================================================
  // Reinject kumi concept & traits in EVE
  using kumi::product_type;
  using kumi::sized_product_type;
  using kumi::is_product_type;

  //================================================================================================
  //! @addtogroup struct
  //! @{
  //!   @struct supports_ordering
  //!   @brief  Register a user-defined type to supports ordering
  //!
  //!   @tparam Type  Type to register as supporting ordering operators
  //!
  //!   By default, instances of `eve::wide<T>` where `T` is an User-Defined Product Type supports
  //!   ordering. However, one can specialize `eve::supports_ordering` for a given type to evaluates
  //!   to `false` in order to disable ordering for this type.
  //!
  //!   Alternatively, any type `T` providing an internal `eve_disable_ordering` type will be
  //!   treated as if `eve::supports_ordering<T>::``value` evaluates to `false`, thus disabling
  //!   ordering operators for `eve::wide<T>`.
  //!
  //!   ### Helper variable template
  //!
  //!   @code
  //!   template<typename Type>
  //!   inline constexpr bool supports_ordering_v = eve::supports_ordering<Type>::value;
  //!   @endcode
  //!
  //! @}
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
  //! @addtogroup struct
  //! @{
  //!   @struct supports_like
  //!   @concept like
  //!
  //!   `like<Wrapper, T>` is a concept that describes a wrapper for which most of the functionality
  //!   for T should be applicable. T is always like T.
  //!
  //!   `like< Wrapper, T>` is true if Wrapper defines a typedef `using is_like = T` or
  //!   specialises `eve::supports_like`.
  //!
  //!   Example: `eve::wide<T>` is `like<T>`.
  //!
  //!   This is used to work with custom structs in eve, see `oop` section in `examples`.
  //! @}
  //================================================================================================


  template<typename Wrapper, typename Self> struct supports_like : std::false_type {};

  template <typename Wrapper, typename Self>
  requires requires(Wrapper) { typename Wrapper::is_like; }
  struct supports_like<Wrapper, Self> :
  std::bool_constant<std::same_as<Self, typename std::remove_cvref_t<Wrapper>::is_like>>
  {};

  template<typename Wrapper, typename Self>
  concept like = std::same_as<std::remove_cvref_t<Wrapper>, Self> ||
                 supports_like<std::remove_cvref_t<Wrapper>, Self>::value;

  //================================================================================================
  //! @addtogroup struct
  //! @{
  //!   @struct product_type_base<Self, ...Fields>
  //!   @brief  a helper CRTP base to declare user defined types easier
  //!
  //!   It will generate a member wise equality.
  //!   It will also generate a lexicographical order for your type, unless !supports_ordering_v<Self>
  //!
  //!   It generated the not mutating operator version from a mutating one (like operator+ from operator+=),
  //!   however does not go further than that (like operator-= b from operator+= and operator-)
  //!   since simd has an instruction for `-` and you want `operator-=` to be declared separately.
  //!
  //! @}
  template <typename Self, typename ... Fields>
  struct product_type_base;

  namespace detail
  {
    std::false_type derived_from_product_type_base_impl(...);

    template <typename Self, typename ... Fields>
    std::true_type derived_from_product_type_base_impl(product_type_base<Self, Fields...> const&);

    template <typename Type>
    concept derived_from_product_type_base = decltype(derived_from_product_type_base_impl(Type{}))::value;
  }

  template <typename Self, typename ... Fields>
  struct product_type_base : kumi::tuple<Fields...>
  {
    using tuple = kumi::tuple<Fields...>;

    EVE_FORCEINLINE friend auto operator+(eve::like<Self> auto x, eve::like<Self> auto y) requires requires { x += y; }
    {
      x += y;
      return x;
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
}

template <eve::detail::derived_from_product_type_base Type>
struct std::tuple_size<Type> : std::tuple_size<typename Type::tuple> {};

template <std::size_t I, eve::detail::derived_from_product_type_base Type>
struct std::tuple_element<I, Type> : std::tuple_element<I, typename Type::tuple> {};
