//==================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : OFW Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <ostream>
#include <string_view>
#include <type_traits>
#include <utility>

#define RBR_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

namespace rbr::detail
{
  // Lightweight container of value in alternatives
  template<typename T, typename V> struct type_or_ { V value; };

  // Type -> String converter
  template<typename T> struct type_name
  {
    static constexpr auto value() noexcept
    {
  #if defined(_MSC_VER )
      std::string_view data(__FUNCSIG__);
      auto i = data.find('<') + 1;
      auto j = data.find(">::value");
      return data.substr(i, j - i);
  #else
      std::string_view data(__PRETTY_FUNCTION__);
      auto i = data.find('=') + 2;
      auto j = data.find_last_of(']');
      return data.substr(i, j - i);
  #endif
    }
  };

  // Helpers for working on list of keys as unique lists - needed by merge and some contains_*
  template<typename... Ks> struct keys {};

  template<typename K, typename Ks> struct contains;

  template<typename... Ks, typename K>
  struct  contains<K, keys<Ks...>> : std::bool_constant<(std::same_as<K,Ks> || ...)>
  {};

  template<typename K, typename Ks, bool>  struct append_if_impl;

  template<typename... Ks, typename K> struct append_if_impl<K,keys<Ks...>,true>
  {
    using type = keys<Ks...>;
  };

  template<typename... Ks, typename K> struct append_if_impl<K,keys<Ks...>,false>
  {
    using type = keys<Ks...,K>;
  };

  template<typename K, typename Ks> struct append_if;

  template<typename K, typename Ks>
  struct append_if : append_if_impl<K,Ks, contains<K, Ks>::value>
  {};

  template<typename K1, typename K2> struct uniques;

  template<typename K1s, typename K2, typename... K2s>
  struct  uniques<K1s, keys<K2,K2s...>>
        : uniques< typename append_if<K2,K1s>::type, keys<K2s...> >
  {};

  template<typename K1s> struct  uniques<K1s, keys<>> { using type = K1s; };

  template<typename K1, typename K2> struct contain_all;

  template<typename K1s, typename... K2s>
  struct  contain_all<K1s, keys<K2s...>> : std::bool_constant<(contains<K2s,K1s>::value && ...)>
  {};

  template<typename K1s>  struct  contain_all<K1s   , keys<>>  : std::false_type {};
  template<typename K2s>  struct  contain_all<keys<>, K2s   >  : std::false_type {};
  template<>              struct  contain_all<keys<>,keys<>>   : std::true_type  {};

  template<typename K1, typename K2>
  struct is_equivalent : std::bool_constant<contain_all<K2,K1>::value && contain_all<K2,K1>::value>
  {};
}

namespace rbr
{
  namespace concepts
  {
    // Keyword concept
    template<typename K> concept keyword = requires( K k )
    {
      typename K::tag_type;
      { K::template accept<int>() } -> std::same_as<bool>;
    };

    // Option concept
    template<typename O> concept option = requires( O const& o )
    {
      { o(typename std::remove_cvref_t<O>::keyword_type{}) }
          -> std::same_as<typename std::remove_cvref_t<O>::value_type>;
    };

    // Type checker concept
    template<typename C> concept type_checker = requires( C const& )
    {
      typename C::template apply<int>::type;
    };

    // keyword parameter exact match
    template<typename Option, auto Keyword>
    concept exactly = std::same_as< typename Option::keyword_type
                                  , std::remove_cvref_t<decltype(Keyword)>
                                  >;
  }

  // Option implementation
  template<concepts::keyword Keyword, typename Value> struct option
  {
    using value_type    = Value;
    using keyword_type  = Keyword;

    constexpr value_type operator()(keyword_type const&) const noexcept { return contents; }
    Value contents;
  };

  // checked_keyword implementation
  template<typename Tag, typename Traits> struct checked_keyword
  {
    using tag_type  = Tag;

    constexpr checked_keyword() {}
    constexpr checked_keyword(Tag, Traits) {}

    template<typename T> static constexpr bool accept()
    {
      return Traits::template apply<std::remove_cvref_t<T>>::value;
    }

    template<typename Type>
    constexpr auto operator=(Type&& v) const noexcept requires( accept<Type>() )
    {
      return option<checked_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires( accept<Type>() )
    {
      return detail::type_or_<checked_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires std::invocable<Type>
    {
      return detail::type_or_<checked_keyword,Type>{RBR_FWD(v)};
    }
  };

  // Keyword accepting a precise type as input
  template<typename Tag, typename Value> struct typed_keyword
  {
    using tag_type  = Tag;

    template<typename T> static constexpr bool accept() { return std::is_same_v<T,Value>; }

    template<typename Type>
    constexpr auto operator=(Type&& v) const noexcept requires( accept<Type>() )
    {
      return option<typed_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires( accept<Type>() )
    {
      return detail::type_or_<typed_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires std::invocable<Type>
    {
      return detail::type_or_<typed_keyword,Type>{RBR_FWD(v)};
    }
  };

  // Keyword accepting any type as input
  template<typename Tag> struct any_keyword
  {
    using tag_type  = Tag;

    template<typename T> static constexpr bool accept()
    {
      return !std::invocable<std::remove_cvref_t<T>>;
    }

    template<typename Type>
    constexpr auto operator=(Type&& v) const noexcept requires( accept<Type>() )
    {
      return option<any_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires( accept<Type>() )
    {
      return detail::type_or_<any_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires std::invocable<std::remove_cvref_t<Type>>
    {
      return detail::type_or_<any_keyword,Type>{RBR_FWD(v)};
    }
  };

  // Flags are keyword/options which value is given by its sole presence
  template<typename Keyword> struct flag_keyword
  {
    constexpr flag_keyword() {}
    constexpr flag_keyword(Keyword const&) {}

    template<typename T> static constexpr bool accept()
    {
      return std::is_same_v<std::true_type, T>;
    }

    using tag_type      = Keyword;
    using keyword_type  = flag_keyword;
    using value_type    = std::true_type;

    template<typename Type>
    constexpr auto operator=(Type&&) const noexcept
    {
      return *this;
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept
    {
      return detail::type_or_<flag_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires std::invocable<Type>
    {
      return detail::type_or_<flag_keyword,Type>{RBR_FWD(v)};
    }

    constexpr std::true_type operator()(keyword_type const&) const noexcept { return {}; }
  };

  // Keyword builder
  template<typename Tag> constexpr flag_keyword<Tag>  flag(Tag) noexcept { return {}; }
  template<typename Tag> constexpr any_keyword<Tag>   keyword(Tag) noexcept { return {}; }

  template<typename Type, typename Tag>
  constexpr typed_keyword<Tag, Type> keyword(Tag) noexcept { return {}; }

  template<concepts::type_checker Checker, typename Tag>
  constexpr checked_keyword<Tag,Checker> keyword(Tag) noexcept { return {}; }

  // Tag for when something is not found in an aggregator
  struct unknown_key {};

  // Option calls aggregator
  template<concepts::option... Ts> struct aggregator : Ts...
  {
    constexpr aggregator(Ts const&...t) noexcept : Ts(t)... {}
    using Ts::operator()...;

    template<concepts::keyword K> constexpr auto operator()(K const &) const noexcept
    {
      return unknown_key {};
    }
  };

  // Settings is a group of options
  template<concepts::option... Opts> struct settings
  {
    using base = aggregator<Opts...>;
    constexpr settings(Opts const&... opts) : content_(opts...) {}

    static constexpr std::ptrdiff_t size() noexcept { return sizeof...(Opts); }

    template<concepts::keyword Key>
    static constexpr auto contains(Key const &) noexcept
    {
      using found = decltype((std::declval<base>())(Key{}));
      return std::bool_constant<!std::same_as<found, unknown_key> >{};
    }

    template<concepts::keyword... Keys>
    static constexpr auto contains_any(Keys... ks) noexcept { return (contains(ks) || ...); }

    template<concepts::keyword... Keys>
    static constexpr auto contains_only(Keys const&...) noexcept
    {
      using current_keys    = detail::keys<typename Opts::keyword_type...>;
      using acceptable_keys = detail::keys<Keys...>;
      using unique_set      = typename detail::uniques<current_keys,acceptable_keys>::type;
      return  detail::is_equivalent<unique_set, acceptable_keys>::value;
    }

    template<concepts::keyword... Keys>
    static constexpr auto contains_none(Keys... ks) noexcept { return !contains_any(ks...); }

    template<concepts::keyword Key> constexpr auto operator[](Key const& k) const noexcept
    {
      return content_(k);
    }

    template<typename Keyword>
    constexpr auto operator[](flag_keyword<Keyword> const&) const noexcept
    {
      return contains(flag_keyword<Keyword>{});
    }

    template<concepts::keyword Key, typename Value>
    constexpr auto operator[](detail::type_or_<Key, Value> const & tgt) const
    {
            if constexpr( contains(Key{}) ) return (*this)[Key{}];
      else  if constexpr( std::is_invocable_v<Value> ) return tgt.value();
      else                                             return tgt.value;
    }

    friend std::ostream& operator<<(std::ostream& os, settings const& s)
    {
      auto show = [&]<typename T>(T t) -> std::ostream&
      {
        if constexpr( requires(T t) { t.show(os); } ) return t.show(os);
        else                                          return os << detail::type_name<T>::value();
      };

      ( ( show(typename Opts::keyword_type::tag_type{}) << " : " << s[typename Opts::keyword_type{}]
          << " (" << detail::type_name<typename Opts::value_type>::value() << ")\n"
        ),...);

      return os;
    }

    base content_;
  };

  template<concepts::option... Opts>
  settings(Opts&&... opts) -> settings<std::remove_cvref_t<Opts>...>;

  // Traits to fetch type of an option from the type of a Settings
  template<typename Settings, auto Keyword, typename Default = unknown_key>
  struct get_type
  {
    using base = std::remove_cvref_t<decltype( std::declval<Settings>()[Keyword])>;
    using type = std::conditional_t< std::same_as<base,unknown_key>, Default, base>;
  };

  template<typename Settings, auto Keyword>
  struct get_type<Settings,Keyword>
  {
    using type = std::remove_cvref_t<decltype( std::declval<Settings>()[Keyword])>;
  };

  template<typename Settings, auto Keyword, typename Default = unknown_key>
  using get_type_t = typename get_type<Settings,Keyword,Default>::type;

  // Merge settings
  template<concepts::option... K1s, concepts::option... K2s>
  constexpr auto merge(settings<K1s...> const& opts, settings<K2s...> const& defs) noexcept
  {
    auto selector = []<typename K, typename Opts>(K const&, Opts const& o, auto const& d)
                    {
                      constexpr K key;
                      if constexpr( Opts::contains(key) ) return (key = o[key]);
                      else                                return (key = d[key]);
                    };

    auto select = [&]<typename... Ks>(detail::keys<Ks...> const&, auto const& os, auto const& ds)
    {
      return settings(selector(Ks{},os,ds)...);
    };

    return select(typename detail::uniques<detail::keys<typename K1s::keyword_type...>
                                          ,detail::keys<typename K2s::keyword_type...>
                                          >::type{},opts,defs);
  }
}

#undef RBR_FWD
