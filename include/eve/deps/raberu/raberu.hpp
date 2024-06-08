//======================================================================================================================
/*
  RABERU - Fancy Parameters Library
  Copyright : RABERU Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#ifndef RABERU_HPP_INCLUDED
#define RABERU_HPP_INCLUDED
//======================================================================================================================
//! @namespace rbr
//! @brief Main Raberu namespace
//======================================================================================================================
namespace rbr
{
  //====================================================================================================================
  //! @namespace rbr::result
  //! @brief Raberu helper traits namespace
  //====================================================================================================================
  namespace result {}
}
#include <type_traits>
#define RBR_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)
namespace rbr::stdfix
{
  template<typename T, typename U >
  concept is_same_impl = std::is_same_v<T, U>;
  template<typename T, typename U >
  concept same_as = is_same_impl<T, U> && is_same_impl<U, T>;
}
namespace rbr::_
{
  template<typename... Ks> struct keys {};
  template<typename K, typename Ks> struct contains;
  template<typename... Ks, typename K>
  struct  contains<K, keys<Ks...>> : std::bool_constant<(stdfix::same_as<K,Ks> || ...)>
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
  template<typename... T> struct types {};
}
#include <cstddef>
#include <type_traits>
#include <ostream>
namespace rbr::concepts
{
  template<typename K> concept keyword = requires( K k )
  {
    typename K::tag_type;
    { K::template accept<int>() } -> stdfix::same_as<bool>;
  };
  template<typename O> concept option = requires( O const& o )
  {
    { o(typename std::remove_cvref_t<O>::keyword_type{}) }
    -> stdfix::same_as<typename std::remove_cvref_t<O>::stored_value_type>;
  };
  template<typename S> concept settings = requires( S const& s )
  {
    typename S::rbr_settings;
  };
  template<typename Option, auto Keyword>
  concept exactly = stdfix::same_as < typename Option::keyword_type
                                    , std::remove_cvref_t<decltype(Keyword)>
                                    >;
}
namespace rbr::_
{
  template<typename K, typename T>
  concept checks_for = requires(K)
  {
    { K::template check<T>() };
  };
  template<typename T>
  concept identifiable = requires(T t)
  {
    { t.identifier };
  };
  template<typename T>
  concept self_identifiable = requires(T t, std::ostream& os)
  {
    { os << t };
  };
  template<typename T, typename V>
  concept displayable = requires(T t, std::ostream& os, V v)
  {
    { t.display(os,v) };
  };
  template<std::size_t N, std::size_t M>
  concept fits = (N <= M);
}
#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string_view>
#include <utility>
namespace rbr::_
{
  template<concepts::keyword T, typename V> struct type_or_
  {
    V value;
    template<concepts::option... Os>
    constexpr decltype(auto) operator()(Os&&... os) const { return fetch(*this, RBR_FWD(os)...); }
  };
  template <typename T> constexpr auto typer() noexcept
  {
#if defined(__clang__)
    constexpr auto pfx = std::string_view("auto rbr::_::typer() [T = ").size();
    constexpr auto sfx = std::string_view("]").size();
    constexpr auto raw = std::string_view(__PRETTY_FUNCTION__);
#elif defined(__GNUC__)
    constexpr auto pfx = std::string_view("constexpr auto rbr::_::typer() [with " "T = ").size();
    constexpr auto sfx = std::string_view("]").size();
    constexpr auto raw = std::string_view(__PRETTY_FUNCTION__);
#elif defined(_MSC_VER)
    constexpr auto pfx = std::string_view("auto __cdecl rbr::_::typer<").size();
    constexpr auto sfx = std::string_view(">(void)").size();
    constexpr auto raw = std::string_view(__FUNCSIG__);
#endif
    auto value = raw;
    value.remove_prefix(pfx);
    value.remove_suffix(sfx);
    constexpr auto size = raw.size() - (pfx + sfx);
    auto fn = [&]<std::size_t... Is>(std::index_sequence<Is...>)
    {
      return std::array<char const, sizeof...(Is) + 1>{value[Is]...};
    };
    return fn(std::make_index_sequence<size>{});
  }
  template<typename T>  inline constexpr auto type_array  = typer<T>();
  template<typename T, auto ID = type_array<T>>
  struct type_t
  {
    static constexpr auto name() { return std::string_view(ID.data(), ID.size());}
  };
  template<typename T>
  inline constexpr auto type  = type_t<T>{};
}
#if !defined(RBR_MAX_LITERAL_SIZE)
#define RBR_MAX_LITERAL_SIZE 32
#endif
namespace rbr
{
  namespace literals
  {
    struct str
    {
      static constexpr std::size_t max_size = RBR_MAX_LITERAL_SIZE;
      char         data_[max_size+1];
      std::uint8_t size_;
      template<std::size_t N, std::size_t... Is>
      requires _::fits<N,max_size>
      constexpr str(const char (&s)[N], std::index_sequence<Is...>) : data_{s[Is]...}, size_(N)
      {}
      template <std::size_t N>
      requires _::fits<N,max_size>
      constexpr str(const char (&s)[N]) : str{s, std::make_index_sequence<N>{}}
      {}
      constexpr std::size_t       size()  const { return size_; }
      constexpr std::string_view  value() const { return std::string_view(&data_[0],size_); }
      friend std::ostream& operator<<(std::ostream& os, str const& s)
      {
        return os << '\'' << s.value() << '\'';
      }
    };
  }
  template<literals::str ID> struct id_
  {
    friend std::ostream& operator<<(std::ostream& os, id_ const&)
    {
      return os << ID;
    }
  };
  namespace literals
  {
    template<str ID> constexpr auto operator""_id() noexcept { return id_<ID>{}; }
  }
}
#include <compare>
#include <ostream>
#include <type_traits>
namespace rbr
{
  template<typename Func> struct call
  {
    constexpr call(Func f) : callable(f) {}
    constexpr auto perform() const { return callable(); }
    Func callable;
  };
  template<concepts::keyword Keyword, typename Value> struct option
  {
    using stored_value_type = std::decay_t<Value>;
    using keyword_type      = Keyword;
    constexpr stored_value_type operator()(keyword_type const&) const noexcept { return contents; }
    stored_value_type contents;
  };
  template<typename Keyword> struct as_keyword
  {
    using tag_type  = Keyword;
    inline constexpr auto operator<=>(as_keyword const&) const noexcept = default;
    template<typename T>
    static constexpr bool accept()
    {
      if      constexpr(stdfix::same_as<std::remove_cvref_t<T>,as_keyword>)             return true;
      else if constexpr(_::checks_for<Keyword,T>)          return Keyword::template check<T>();
      else                                                                              return true;
    }
    template<typename Type>
    constexpr auto operator=(Type&& v) const noexcept requires( accept<Type>() )
    {
      return option<Keyword,Type>{RBR_FWD(v)};
    }
    template<typename V> std::ostream& show(std::ostream& os, V const& v) const
    {
      if constexpr(_::displayable<Keyword,V>) return Keyword{}.display(os,v);
      else
      {
        if constexpr(_::identifiable<Keyword>) os << Keyword::identifier;
        else                                        os << '[' << _::type<Keyword>.name() << ']';
        return os << " : " << v << " (" << _::type<V>.name() << ')';
      }
    }
    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept requires( accept<Type>() )
    {
      return _::type_or_<Keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }
    template<typename Func> constexpr auto operator|(call<Func>&& v) const noexcept
    {
      return _::type_or_<Keyword,call<Func>>{RBR_FWD(v)};
    }
    template<concepts::option... Os>
    constexpr decltype(auto) operator()(Os&&... o) const { return fetch(Keyword{}, RBR_FWD(o)...); }
  };
  template<typename ID, template<class> class Checker>
  struct checked_keyword : as_keyword<checked_keyword<ID, Checker>>
  {
    using as_keyword<checked_keyword<ID, Checker>>::operator=;
    template<typename T>  static constexpr bool check() { return Checker<T>::value; }
    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(_::self_identifiable<ID>) os << ID{};
      else
      {
        if constexpr(_::identifiable<ID>) os << ID::identifier;
        else os << '[' << _::type<ID>.name() << ']';
      }
      os << " ::: " << v << " (" << _::type<V>.name() << ") checked by '";
      return os << _::type<Checker<V>>.name() << '\'';
    }
  };
  template<typename ID, typename Type>
  struct typed_keyword  : as_keyword<typed_keyword<ID, Type>>
  {
    using as_keyword<typed_keyword<ID, Type>>::operator=;
    template<typename T>
    static constexpr bool check() { return std::is_same_v<std::remove_cvref_t<T>,Type>; }
    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(_::self_identifiable<ID>) os << ID{};
      else
      {
        if constexpr(_::identifiable<ID>) os << ID::identifier;
        else os << '[' << _::type<ID>.name() << ']';
      }
      return os << " : " << v << " of type '" << _::type<V>.name() << '\'';
    }
  };
  template<typename ID>
  struct any_keyword   : as_keyword<any_keyword<ID>>
  {
    using as_keyword<any_keyword<ID>>::operator=;
    using id_type = ID;
    template<typename V>
    std::ostream& display(std::ostream& os, V const& v) const
    {
      if constexpr(_::self_identifiable<ID>) os << ID{};
      else
      {
        if constexpr(_::identifiable<ID>) os << ID::identifier;
        else os << '[' << _::type<ID>.name() << ']';
      }
      return os << " : " << v << " (" << _::type<V>.name() << ')';
    }
  };
  template<typename ID> struct flag_keyword
  {
    constexpr flag_keyword() {}
    constexpr flag_keyword(ID const&) {}
    using id_type = ID;
    template<typename T> static constexpr bool accept()
    {
      return std::is_same_v<std::true_type, T>;
    }
    std::ostream& show(std::ostream& os, bool) const
    {
      if constexpr(_::identifiable<ID>) os << ID::identifier;
      else if constexpr(_::self_identifiable<ID>) os << ID{};
      else os << '[' << _::type<ID>.name() << ']';
      return os << " : set";
    }
    using tag_type          = ID;
    using keyword_type      = flag_keyword;
    using stored_value_type = bool;
    template<typename Type>
    constexpr auto operator=(Type&&) const noexcept { return *this; }
    template<typename Type>
    constexpr auto operator|(Type&& v) const noexcept
    {
      return _::type_or_<flag_keyword,std::remove_cvref_t<Type>>{RBR_FWD(v)};
    }
    template<typename Func> constexpr auto operator|(call<Func>&& v) const noexcept
    {
      return _::type_or_<flag_keyword,call<Func>>{RBR_FWD(v)};
    }
    constexpr auto operator()(keyword_type const&) const noexcept { return true; }
    template<typename O0, typename O1, typename... Os>
    constexpr decltype(auto) operator()(O0&&, O1&&, Os&&... ) const
    {
      return    stdfix::same_as<keyword_type, typename std::remove_cvref_t<O0>::keyword_type>
            ||  stdfix::same_as<keyword_type, typename std::remove_cvref_t<O1>::keyword_type>
            || (stdfix::same_as<keyword_type, typename std::remove_cvref_t<Os>::keyword_type> || ...);
    }
  };
  template<typename Tag>
  constexpr flag_keyword<Tag>  flag([[maybe_unused]] Tag id) noexcept { return {}; }
  template<typename ID>
  constexpr any_keyword<ID> keyword([[maybe_unused]] ID id) noexcept { return {}; }
  template<template<class> class Checker, typename ID>
  constexpr checked_keyword<ID,Checker> keyword([[maybe_unused]] ID id) noexcept { return {}; }
  template<typename Type, typename ID>
  constexpr typed_keyword<ID, Type> keyword([[maybe_unused]] ID id) noexcept { return {}; }
  namespace literals
  {
    template<str ID>
    constexpr auto operator""_kw() noexcept { return any_keyword<id_<ID>>{}; }
    template<str ID>
    constexpr auto operator""_fl() noexcept { return flag_keyword<id_<ID>>{}; }
  }
}
#include <cstddef>
#include <ostream>
#include <type_traits>
namespace rbr
{
  struct unknown_key { using type = unknown_key; };
  template<concepts::option... Ts> struct aggregator : Ts...
  {
    constexpr aggregator(Ts const&...t) noexcept : Ts(t)... {}
    using Ts::operator()...;
    template<concepts::keyword K> constexpr auto operator()(K const &) const noexcept
    {
      return unknown_key {};
    }
  };
  template<concepts::option... Opts> struct settings
  {
    using rbr_settings = void;
    using base = aggregator<Opts...>;
    constexpr settings(Opts const&... opts) : content_(opts...) {}
    static constexpr std::ptrdiff_t size() noexcept { return sizeof...(Opts); }
    template<concepts::keyword Key>
    static constexpr auto contains([[maybe_unused]] Key const& kw) noexcept
    {
      using found = decltype((std::declval<base>())(Key{}));
      return !stdfix::same_as<found, unknown_key>;
    }
    template<concepts::keyword... Keys>
    static constexpr auto contains_any(Keys... ks) noexcept { return (contains(ks) || ...); }
    template<concepts::keyword... Keys>
    static constexpr auto contains_only([[maybe_unused]] Keys const&... ks) noexcept
    {
      using current_keys    = _::keys<typename Opts::keyword_type...>;
      using acceptable_keys = _::keys<Keys...>;
      using unique_set      = typename _::uniques<current_keys,acceptable_keys>::type;
      return  _::is_equivalent<unique_set, acceptable_keys>::value;
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
    constexpr auto operator[](_::type_or_<Key, Value> const & tgt) const
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
  settings(Opts const&... opts) -> settings<Opts...>;
}
namespace rbr
{
  namespace _
  {
    template<typename K, concepts::keyword... Kept>
    struct filter
    {
      using type = _::keys<Kept...>;
      template<typename T> constexpr auto operator+(keys<T> const&) const
      {
        using kw_t = typename T::keyword_type;
        if constexpr(!stdfix::same_as<K, typename kw_t::tag_type>)  return filter<K, Kept..., kw_t>{};
        else                                                        return *this;
      }
    };
    template< typename K, typename S> struct select_keys;
    template< typename K, concepts::option... Os>
    struct  select_keys<K,rbr::settings<Os...>>
          : decltype((filter<typename K::tag_type>{}  + ... +  _::keys<Os>{}))
    {
    };
  }
  template<concepts::keyword K, concepts::option... O>
  [[nodiscard]] constexpr auto drop([[maybe_unused]] K const& k, settings<O...> const& s)
  {
    using selected_keys_t = typename _::select_keys<K,settings<O...>>::type;
    return [&]<typename ... Ks>( _::keys<Ks...> )
    {
      return rbr::settings{ (Ks{} = s[Ks{}] )...};
    }(selected_keys_t{});
  }
  namespace result
  {
    template<concepts::keyword K, concepts::option... O>
    struct drop
    {
      using type = decltype( rbr::drop(std::declval<K>(),std::declval<O>()...) );
    };
    template<concepts::keyword K, concepts::option... O>
    using drop_t = typename drop<K,O...>::type;
  }
}
namespace rbr
{
  template<concepts::keyword K, concepts::option... Os>
  constexpr decltype(auto) fetch(K const& k, Os const&... os)
  {
    auto const opts = settings(os...);
    return opts[k];
  }
  template<concepts::keyword K, typename V, concepts::option... Os>
  constexpr decltype(auto) fetch(_::type_or_<K, V> const& k, Os const&... os)
  {
    auto const opts = settings(os...);
    return opts[k];
  }
  template<typename K, concepts::settings Settings>
  constexpr decltype(auto) fetch(K const& k, Settings const& opts)
  {
    return opts[k];
  }
  namespace result
  {
    template<auto Keyword, typename... Sources> struct fetch;
    template<auto Keyword, concepts::option... Os>
    struct fetch<Keyword, Os...>
    {
      using type = decltype( rbr::fetch(Keyword, std::declval<Os>()...) );
    };
    template<auto Keyword, concepts::settings Settings>
    struct fetch<Keyword, Settings>
    {
      using type = decltype( rbr::fetch(Keyword, std::declval<Settings>()) );
    };
    template<auto Keyword, typename... Sources>
    using fetch_t = typename fetch<Keyword,Sources...>::type;
  }
}
namespace rbr
{
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
  constexpr auto keywords([[maybe_unused]]rbr::settings<Opts...> const& s)
  {
    return result::keywords_t<rbr::settings<Opts...>,List>{typename Opts::keyword_type{}...};
  }
  template<template<typename...> class List, typename... Opts>
  constexpr auto values(rbr::settings<Opts...> const& s)
  {
    return result::values_t<rbr::settings<Opts...>,List>{ s[typename Opts::keyword_type{}]... };
  }
}
namespace rbr
{
  template<concepts::settings S1, concepts::settings S2>
  struct  is_equivalent
        : std::bool_constant<   _::is_equivalent< result::keywords_t<S1,_::keys>
                                                , result::keywords_t<S2,_::keys>
                                                >::value
                            &&  _::is_equivalent< result::keywords_t<S2,_::keys>
                                                , result::keywords_t<S1,_::keys>
                                                >::value
                            >
  {};
  template<concepts::settings S1, concepts::settings S2>
  inline constexpr bool is_equivalent_v = is_equivalent<S1,S2>::value;
}
namespace rbr
{
  template<concepts::option... K1s, concepts::option... K2s>
  constexpr auto merge(settings<K1s...> const& opts, settings<K2s...> const& defs) noexcept
  {
    auto selector = []<typename K, typename Opts>(K const&, Opts const& o, auto const& d)
                    {
                      constexpr K key;
                      if constexpr( Opts::contains(key) ) return (key = o[key]);
                      else                                return (key = d[key]);
                    };
    auto select = [&]<typename... Ks>(_::keys<Ks...> const&, auto const& os, auto const& ds)
    {
      return settings(selector(Ks{},os,ds)...);
    };
    return select(typename _::uniques<_::keys<typename K1s::keyword_type...>
                                          ,_::keys<typename K2s::keyword_type...>
                                          >::type{},opts,defs);
  }
  namespace result
  {
    template<concepts::settings S1, concepts::settings S2>
    struct merge
    {
      using type = decltype( rbr::merge(std::declval<S1>(),std::declval<S2>()) );
    };
    template<concepts::settings S1, concepts::settings S2>
    using merge_t = typename merge<S1,S2>::type;
  }
}
#undef RBR_FWD
#endif
