//==================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#ifndef RABERU_HPP_INCLUDED
#define RABERU_HPP_INCLUDED

#include <array>
#include <cstring>
#include <ostream>
#include <string_view>
#include <type_traits>
#include <utility>

#define RBR_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

namespace rbr::concepts
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
    -> std::same_as<typename std::remove_cvref_t<O>::stored_value_type>;
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

namespace rbr::detail
{
  // Lightweight container of value in alternatives
  template<concepts::keyword T, typename V> struct type_or_
  {
    V value;

    template<concepts::option... Os>
    constexpr decltype(auto) operator()(Os&&... os) const { return fetch(*this, RBR_FWD(os)...); }
  };

  // Type -> String converter
  template <typename T> constexpr auto type_name() noexcept
  {
    std::string_view name, prefix, suffix;
  #ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto rbr::detail::type_name() [T = ";
    suffix = "]";
  #elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto rbr::detail::type_name() [with T = ";
    suffix = "]";
  #elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "auto __cdecl rbr::detail::type_name<";
    suffix = ">(void)";
  #endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
  }

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
  // ID user defined literals
  namespace literals
  {
    template<std::size_t N> struct str_
    {
      std::array<char,N> data;

      template <std::size_t... Is>
      constexpr str_(const char (&str)[N], std::index_sequence<Is...>) :data{str[Is]...} {}
      constexpr str_(const char (&str)[N]) : str_{str, std::make_index_sequence<N>{}} {}

      static constexpr  auto  size()  { return N; }
      auto value() const { return std::string_view(&data[0],strlen(&data[0])); }
    };

    template<std::size_t N> str_(const char (&str)[N]) -> str_<N>;
  }

  template<literals::str_ ID> struct id_
  {
    friend std::ostream& operator<<(std::ostream& os, id_ const&)
    {
      return os << '\'' << ID.value() << '\'';
    }
  };

  namespace literals
  {
    template<str_ ID> constexpr auto operator""_id() noexcept { return id_<ID>{}; }
  }

  // Callable alternative wrapper
  template<typename Func>
  struct call
  {
    constexpr call(Func f) : callable(f) {}
    constexpr auto perform() const { return callable(); }
    Func callable;
  };

  // Option implementation
  template<concepts::keyword Keyword, typename Value> struct option
  {
    using stored_value_type    = Value;
    using keyword_type  = Keyword;

    constexpr stored_value_type operator()(keyword_type const&) const noexcept { return contents; }
    Value contents;
  };

// Base class for custom keyword
  template<typename Keyword> struct as_keyword
  {
    using tag_type  = Keyword;

    inline constexpr auto operator<=>(as_keyword const&) const noexcept = default;

    template<typename T> static constexpr bool accept()
    {
      if constexpr( requires(Keyword) { Keyword::template check<T>(); } )
        return Keyword::template check<T>();
      else
        return true;
    }

    template<typename Type>
    constexpr auto operator=(Type&& v) const noexcept requires( accept<Type>() )
    {
      return option<Keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename V> std::ostream& show(std::ostream& os, V const& v) const
    {
      if constexpr(  requires(Keyword t) { t.display(os,v); } ) return Keyword{}.display(os,v);
      else
      {
        os << '[' << detail::type_name<Keyword>() << ']';
        return os << " : " << v << " (" << detail::type_name<V>() << ')';
      }
    }

    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires( accept<Type>() )
    {
      return detail::type_or_<Keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }

    template<typename Func> constexpr auto operator|(call<Func>&& v) const noexcept
    {
      return detail::type_or_<Keyword,call<Func>>{RBR_FWD(v)};
    }

    template<concepts::option... Os>
    constexpr decltype(auto) operator()(Os&&... o) const { return fetch(Keyword{}, RBR_FWD(o)...); }
  };

  // checked_keyword implementation
  template<typename Tag, typename Traits>
  struct checked_keyword : as_keyword<checked_keyword<Tag, Traits>>
  {
    constexpr checked_keyword() {}
    constexpr checked_keyword(Tag, Traits) {}

    template<typename T> static constexpr bool check()
    {
      return Traits::template apply<std::remove_cvref_t<T>>::value;
    }

    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(  requires(Tag t) { os << Tag{}; } ) os << Tag{};
      else os << '[' << detail::type_name<Tag>() << ']';

      os << " ::: " << v << " (" << detail::type_name<V>() << ") checked by '";
      return os << detail::type_name<Traits>() << '\'';
    }

    using as_keyword<checked_keyword<Tag, Traits>>::operator=;
  };

  // Keyword accepting a precise type as input
  template<typename Tag, typename Value>
  struct typed_keyword  : as_keyword<typed_keyword<Tag, Value>>
  {
    template<typename T> static constexpr bool check() { return std::is_same_v<T,Value>; }

    using as_keyword<typed_keyword<Tag, Value>>::operator=;

    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(  requires(Tag t) { os << Tag{}; } ) os << Tag{};
      else os << '[' << detail::type_name<Tag>() << ']';

      return os << " : " << v << " [[" << detail::type_name<V>() << "]]";
    }
  };

  // Keyword accepting any type as input
  template<typename Tag>
  struct any_keyword   : as_keyword<any_keyword<Tag>>
  {
    using as_keyword<any_keyword<Tag>>::operator=;

    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(requires(Tag t) { os << Tag{}; })  os << Tag{};
      else                                            os << '[' << detail::type_name<Tag>() << ']';

      return os << " : " << v << " (" << detail::type_name<V>() << ')';
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

    std::ostream& show(std::ostream& os, bool) const
    {
      return os << Keyword{} << " : set";
    }

    using tag_type          = Keyword;
    using keyword_type      = flag_keyword;
    using stored_value_type = std::true_type;

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

    template<typename Func> constexpr auto operator|(call<Func>&& v) const noexcept
    {
      return detail::type_or_<flag_keyword,call<Func>>{RBR_FWD(v)};
    }

    constexpr std::true_type operator()(keyword_type const&) const noexcept { return {}; }

    template<typename O0, typename O1, typename... Os>
    constexpr decltype(auto) operator()(O0&&, O1&&, Os&&... ) const
    {
      return    std::same_as<keyword_type , typename std::remove_cvref_t<O0>::keyword_type>
            ||  std::same_as<keyword_type , typename std::remove_cvref_t<O1>::keyword_type>
            || (std::same_as<keyword_type, typename std::remove_cvref_t<Os>::keyword_type> || ...);
    }
  };

  // Keyword builder
  template<typename Tag> constexpr flag_keyword<Tag>  flag(Tag) noexcept { return {}; }
  template<typename Tag> constexpr any_keyword<Tag>   keyword(Tag) noexcept { return {}; }

  template<concepts::type_checker Checker, typename Tag>
  constexpr checked_keyword<Tag,Checker> keyword(Tag) noexcept { return {}; }

  template<typename Type, typename Tag>
  constexpr typed_keyword<Tag, Type> keyword(Tag) noexcept { return {}; }

  // Keyword/Flag-type user defined literals
  namespace literals
  {
    template<str_ ID>
    constexpr auto operator""_kw() noexcept { return any_keyword<id_<ID>>{}; }

    template<str_ ID>
    constexpr auto operator""_fl() noexcept { return flag_keyword<id_<ID>>{}; }
  }

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
      if constexpr( contains(Key{}) )                           return (*this)[Key{}];
      else  if constexpr( requires(Value t) { t.perform(); } )  return tgt.value.perform();
      else                                                      return tgt.value;
    }

    friend std::ostream& operator<<(std::ostream& os, settings const& s)
    {
      auto show = [&]<typename T, typename V>(T t, V const& v) -> std::ostream&
      {
        return t.show(os,v) << "\n";
      };

      (show(typename Opts::keyword_type{}, s[typename Opts::keyword_type{}]), ...);

      return os;
    }

    base content_;
  };

  template<concepts::option... Opts>
  settings(Opts&&... opts) -> settings<std::remove_cvref_t<Opts>...>;

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

  // Drop keyword from settings
  namespace detail
  {
    template<typename K, concepts::keyword... Kept>
    struct filter
    {
      using type = detail::keys<Kept...>;

      template<typename T> constexpr auto operator+(keys<T> const&) const
      {
        using kw_t = typename T::keyword_type;
        if constexpr(!std::same_as<K, typename kw_t::tag_type>)  return filter<K, Kept..., kw_t>{};
        else                                            return *this;
      }
    };

    template< typename K, typename S> struct select_keys;

    template< typename K, concepts::option... Os>
    struct  select_keys<K,rbr::settings<Os...>>
          : decltype((filter<typename K::tag_type>{}  + ... +  detail::keys<Os>{}))
    {
    };
  }

  template<concepts::keyword K, concepts::option... Os>
  constexpr auto drop(K const&, settings<Os...> const& os)
  {
    using selected_keys_t = typename detail::select_keys<K,settings<Os...>>::type;

    return [&]<typename ... Ks>( detail::keys<Ks...> )
    {
      // Rebuild a new settings by going over the keys that we keep
      return rbr::settings{ (Ks{} = os[Ks{}] )...};
    }(selected_keys_t{});
  }

  // Standalone fetch one keyword inside N
  template<concepts::keyword K, concepts::option... Os>
  constexpr decltype(auto) fetch(K const& kw, Os const&... os)
  {
    auto const opts = settings(os...);
    return opts[kw];
  }

  template<concepts::keyword K, typename V, concepts::option... Os>
  constexpr decltype(auto) fetch(detail::type_or_<K, V> const& kw, Os const&... os)
  {
    auto const opts = settings(os...);
    return opts[kw];
  }

  template<typename K, typename Settings>
  constexpr decltype(auto) fetch(K const& kw, Settings const& opts)
  {
    return opts[kw];
  }

  namespace result
  {
    template<auto Keyword, typename... Sources> struct fetch;

    template<auto Keyword, concepts::option... Os>
    struct fetch<Keyword, Os...>
    {
      using type = decltype( rbr::fetch(Keyword, Os{}...) );
    };

    template<auto Keyword, typename Settings>
    struct fetch<Keyword, Settings>
    {
      using type = decltype( rbr::fetch(Keyword, std::declval<Settings>()) );
    };

    template<auto Keyword, typename... Sources>
    using fetch_t = typename fetch<Keyword,Sources...>::type;
  }

  // Global keyword/value_type types extractors
  template<typename... T> struct types {};

  namespace result
  {
    template<typename Settings, template<typename...> class List = types> struct keywords;
    template<typename Settings, template<typename...> class List = types> struct values;

    template<typename... Opts, template<typename...> class List>
    struct keywords<settings<Opts...>, List>
    {
      using type = List<typename Opts::keyword_type...>;
    };

    template<typename... Opts, template<typename...> class List>
    struct values<settings<Opts...>, List>
    {
      using type = List<typename Opts::stored_value_type...>;
    };

    template<typename Settings, template<typename...> class List = types>
    using keywords_t = typename keywords<Settings,List>::type;

    template<typename Settings, template<typename...> class List = types>
    using values_t = typename values<Settings,List>::type;
  }

  template<template<typename...> class List, typename... Opts>
  auto keywords(rbr::settings<Opts...> const&)
  {
    return result::keywords_t<rbr::settings<Opts...>,List>{typename Opts::keyword_type{}...};
  }

  template<template<typename...> class List, typename... Opts>
  auto values(rbr::settings<Opts...> const& o)
  {
    return result::values_t<rbr::settings<Opts...>,List>{ o[typename Opts::keyword_type{}]... };
  }
}

#undef RBR_FWD
#endif
