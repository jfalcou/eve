//==================================================================================================
/**
  RABERU - Fancy Parameters Library
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <type_traits>
#include <utility>

namespace rbr
{
  // Lightweight container of value
  template<typename T, typename V> struct type_or_ { V value; };

  // Turn any type into a RegularType info carrier
  template<typename T> struct keyword_type
  {
    using type        = keyword_type<T>;
    template<typename V> constexpr auto operator=(V&& v) const noexcept;
    template<typename V> constexpr auto operator|(V&& value) const noexcept
    {
      return type_or_<T,V>{std::forward<V>(value)};
    }
  };

  // Keyword_type generator
  template<typename T> inline constexpr const keyword_type<T> keyword = {};

  namespace detail
  {
    // Turn a Type+Value pair into a Callable
    template<typename Callable> struct linked_value : Callable
    {
      constexpr linked_value( Callable f) noexcept : Callable(f) {}
      using Callable::operator();
    };

    // Build the type->value lambda capture
    template<typename Key, typename T> constexpr auto link(T&& v) noexcept
    {
      if constexpr( std::is_lvalue_reference_v<T> )
        return linked_value( [&v](Key const&) constexpr -> decltype(auto) { return v; } );
      else
        return linked_value( [w = std::move(v)](Key const&) constexpr -> T const& { return w; } );
    }

    // Don't relink already linked values
    template<typename Key, typename C> constexpr auto link(linked_value<C>&& v) noexcept
    {
      return std::forward<linked_value<C>>(v);
    }

    // Type notifying that we can't find a given key
    struct unknown_key { template<typename... T> unknown_key(T&&...) {} };

    // Check if the key we used is correct
    template<typename T> inline constexpr bool is_unknown_v              = false;
    template<>           inline constexpr bool is_unknown_v<unknown_key> = true;

    // Aggregate lambdas and give them a operator(Key)-like interface
    template<typename... Ts> struct aggregator : Ts...
    {
      constexpr aggregator(Ts... t) noexcept : Ts(t)... {}
      using Ts::operator()...;

      template<typename K> constexpr auto operator()(keyword_type<K> const&) const noexcept
      {
        // If not found before, return the unknown_key value
        return unknown_key{};
      }
    };
  }

  // Build a key-value from an option object
  template<typename T>
  template<typename V> constexpr auto keyword_type<T>::operator=(V&& v) const noexcept
  {
    return detail::link<keyword_type<T>>(std::forward<V>(v));
  }

  // Extract tag from an Option
  template<typename O> struct tag { using type = keyword_type<O>; };
  template<typename O> using  tag_t = typename tag<O>::type;

  // settings is an unordered set of values accessible via their types
  template<typename... Ts> struct settings
  {
    using parent = detail::aggregator<detail::linked_value<Ts>...>;

    constexpr settings( detail::linked_value<Ts>... ts ) : content_( ts... ) {}

    template<typename... Vs>
    constexpr settings( Vs&&... v )
            : content_( detail::link<tag_t<std::decay_t<Vs>>>( std::forward<Vs>(v))... )
    {}

    static constexpr std::ptrdiff_t size() noexcept { return sizeof...(Ts); }

    // Named options interface
    template<typename T> static constexpr bool contains(keyword_type<T> const&) noexcept
    {
      using found = decltype(std::declval<parent>()(tag_t<T>{}));
      return !detail::is_unknown_v<found>;
    }

    template<typename T>
    constexpr decltype(auto) operator[](keyword_type<T> const& tgt) const noexcept
    {
      return content_(tgt);
    }

    template<typename T, typename V>
    constexpr decltype(auto) operator[](type_or_<T,V> const& tgt) const
    {
            if constexpr( contains(keyword_type<T>{}) )             return content_( keyword_type<T>{} );
      else  if constexpr( std::is_invocable_v<V,keyword_type<T>> )  return tgt.value( keyword_type<T>{} );
      else                                                          return tgt.value;
    }

    parent content_;
  };

  template<typename... Vs>
  settings( Vs&&... v ) ->  settings< decltype( detail::link< tag_t<std::decay_t<Vs>>  >
                                                            ( std::forward<Vs>(v) )
                                              )...
                                    >;
}
