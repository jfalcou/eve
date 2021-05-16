//==================================================================================================
/**
  KUMI - Compact Tuple Tools
  Copyright : OFW Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <iosfwd>
#include <utility>

#define KUMI_FWD(...) static_cast<decltype(__VA_ARGS__) &&>(__VA_ARGS__)

namespace kumi
{
  //================================================================================================
  // Constant integers
  //================================================================================================
  template<std::size_t N> struct index_t
  {
    static constexpr auto value = N;
    constexpr inline      operator std::size_t() const noexcept { return N; }
  };

  template<std::size_t N> inline constexpr index_t<N> const index = {};

  //================================================================================================
  // UDL for constant indexing like 42_c
  //================================================================================================
  namespace literals
  {
    template<char... c> constexpr auto b10()
    {
      auto value = 0ULL;
      ((value = value * 10 + (c - '0')), ...);
      return value;
    }
    template<char... c> constexpr auto operator"" _c() noexcept { return index<b10<c...>()>; }
  }

  //================================================================================================
  // Implementation detail
  //================================================================================================
  namespace detail
  {
    //==============================================================================================
    // Helper concepts
    //==============================================================================================
    template<typename From, typename To> struct is_piecewise_constructible;
    template<typename From, typename To> struct is_piecewise_convertible;

    template<template<class...> class Box, typename... From, typename... To>
    struct is_piecewise_convertible<Box<From...>, Box<To...>>
    {
      static constexpr bool value = (... && std::convertible_to<From, To>);
    };

    template<template<class...> class Box, typename... From, typename... To>
    struct is_piecewise_constructible<Box<From...>, Box<To...>>
    {
      static constexpr bool value = (... && std::is_constructible_v<To, From>);
    };

    template<typename From, typename To>
    concept piecewise_convertible = detail::is_piecewise_convertible<From, To>::value;

    template<typename From, typename To>
    concept piecewise_constructible = detail::is_piecewise_constructible<From, To>::value;

    template<typename T, typename... Args>
    concept implicit_constructible = requires(Args... args)
    {
      T {args...};
    };

    //==============================================================================================
    // Tuple leaf binder tricks
    //==============================================================================================
    template<std::size_t I, typename T> struct leaf
    {
      T value;
    };

    template<std::size_t I, typename T> constexpr T &get_leaf(leaf<I, T> &arg) noexcept
    {
      return arg.value;
    }

    template<std::size_t I, typename T> constexpr T &&get_leaf(leaf<I, T> &&arg) noexcept
    {
      return static_cast<T &&>(arg.value);
    }

    template<std::size_t I, typename T>
    constexpr T const &&get_leaf(leaf<I, T> const &&arg) noexcept
    {
      return static_cast<T const &&>(arg.value);
    }

    template<std::size_t I, typename T> constexpr T const &get_leaf(leaf<I, T> const &arg) noexcept
    {
      return arg.value;
    }

    template<typename ISeq, typename... Ts> struct binder;

    template<auto... Is, typename... Ts>
    struct binder<std::index_sequence<Is...>, Ts...> : leaf<Is, Ts>...
    {
    };

    //==============================================================================================
    // Fold helpers
    //==============================================================================================
    template<typename F, typename T> struct foldable
    {
      F func;
      T value;

      template<typename W>
      friend constexpr decltype(auto) operator>>(foldable &&x, foldable<F, W> &&y)
      {
        return detail::foldable {x.func, x.func(y.value, x.value)};
      }

      template<typename W>
      friend constexpr decltype(auto) operator<<(foldable &&x, foldable<F, W> &&y)
      {
        return detail::foldable {x.func, x.func(x.value, y.value)};
      }
    };

    template<class F, class T> foldable(const F &, T &&) -> foldable<F, T>;
  }

  //==============================================================================================
  // Concept
  //==============================================================================================
  template<typename T>
  concept product_type = std::remove_cvref_t<T>::is_product_type;

  template<typename T, std::size_t N>
  concept sized_product_type = product_type<T> &&(T::size() == N);

  //================================================================================================
  // Forward declaration
  //================================================================================================

  template<typename... Ts> struct tuple;

  //================================================================================================
  // Pass every elements of the tuple to f
  //================================================================================================
  template<typename Function, product_type Tuple>
  constexpr decltype(auto) apply(Function &&f, Tuple &&t)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return KUMI_FWD(f)(detail::get_leaf<I>(KUMI_FWD(t).impl)...);
    }
    (std::make_index_sequence<std::remove_cvref_t<Tuple>::size()>());
  }

  //================================================================================================
  // Apply f to each element of tuple and returns a continuation
  //================================================================================================
  template<typename Function, typename... Ts> constexpr void for_each(Function f, tuple<Ts...> &t)
  {
    [&]<std::size_t... I>(std::index_sequence<I...>) { (f(detail::get_leaf<I>(t.impl)), ...); }
    (std::make_index_sequence<sizeof...(Ts)>());
  }

  template<typename Function, typename... Ts>
  constexpr void for_each(Function f, tuple<Ts...> const &t)
  {
    [&]<std::size_t... I>(std::index_sequence<I...>) { (f(detail::get_leaf<I>(t.impl)), ...); }
    (std::make_index_sequence<sizeof...(Ts)>());
  }

  template<typename Function, typename... Ts>
  constexpr void for_each_index(Function f, tuple<Ts...> &t)
  {
    [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      (f(index<I>, detail::get_leaf<I>(t.impl)), ...);
    }
    (std::make_index_sequence<sizeof...(Ts)>());
  }

  template<typename Function, typename... Ts>
  constexpr void for_each_index(Function f, tuple<Ts...> const &t)
  {
    [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      (f(index<I>, detail::get_leaf<I>(t.impl)), ...);
    }
    (std::make_index_sequence<sizeof...(Ts)>());
  }

  //================================================================================================
  // Main tuple class
  //================================================================================================
  template<typename... Ts> struct tuple
  {
    static constexpr bool                                          is_product_type = true;
    detail::binder<std::make_index_sequence<sizeof...(Ts)>, Ts...> impl;

    //==============================================================================================
    // Access
    //==============================================================================================
    template<std::size_t I>
    requires(I < sizeof...(Ts)) constexpr decltype(auto) operator[](index_t<I>) &noexcept
    {
      return detail::get_leaf<I>(impl);
    }

    template<std::size_t I>
    requires(I < sizeof...(Ts)) constexpr decltype(auto) operator[](index_t<I>) &&noexcept
    {
      return detail::get_leaf<I>(static_cast<decltype(impl) &&>(impl));
    }

    template<std::size_t I>
    requires(I < sizeof...(Ts)) constexpr decltype(auto) operator[](index_t<I>) const &&noexcept
    {
      return detail::get_leaf<I>(static_cast<decltype(impl) const &&>(impl));
    }

    template<std::size_t I>
    requires(I < sizeof...(Ts)) constexpr decltype(auto) operator[](index_t<I>) const &noexcept
    {
      return detail::get_leaf<I>(impl);
    }

    //==============================================================================================
    // Tuple as functional object
    //==============================================================================================
    template<typename Function>
    constexpr decltype(auto)
    operator()(Function &&f) const &noexcept(noexcept(kumi::apply(KUMI_FWD(f), *this)))
    {
      return kumi::apply(KUMI_FWD(f), *this);
    }

    template<typename Function>
    constexpr decltype(auto)
    operator()(Function &&f) &noexcept(noexcept(kumi::apply(KUMI_FWD(f), *this)))
    {
      return kumi::apply(KUMI_FWD(f), *this);
    }

    template<typename Function>
    constexpr decltype(auto) operator()(Function &&f) const &&noexcept(
        noexcept(kumi::apply(KUMI_FWD(f), static_cast<tuple const &&>(*this))))
    {
      return kumi::apply(KUMI_FWD(f), static_cast<tuple const &&>(*this));
    }

    template<typename Function>
    constexpr decltype(auto) operator()(Function &&f) &&noexcept(
        noexcept(kumi::apply(KUMI_FWD(f), static_cast<tuple &&>(*this))))
    {
      return kumi::apply(KUMI_FWD(f), static_cast<tuple &&>(*this));
    }

    //==============================================================================================
    // Extract a sub-rage of tuple element
    //==============================================================================================
    template<std::size_t I0, std::size_t I1>
    requires((I1 - I0) <= sizeof...(Ts))
        [[nodiscard]] constexpr auto extract(index_t<I0> const &,
                                             index_t<I1> const &) const noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N + I0, tuple>...> {(*this)[index<N + I0>]...};
      }
      (std::make_index_sequence<I1 - I0>());
    }

    template<std::size_t I0, std::size_t I1>
    requires((I1 - I0) <= sizeof...(Ts))
        [[nodiscard]] constexpr auto extract(index_t<I0> const &, index_t<I1> const &) noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N + I0, tuple>...> {(*this)[index<N + I0>]...};
      }
      (std::make_index_sequence<I1 - I0>());
    }

    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts))
        [[nodiscard]] constexpr auto extract(index_t<I0> const &) const noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N + I0, tuple>...> {(*this)[index<N + I0>]...};
      }
      (std::make_index_sequence<sizeof...(Ts) - I0>());
    }

    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts)) [[nodiscard]] constexpr auto extract(index_t<I0> const &) noexcept
    {
      return [&]<std::size_t... N>(std::index_sequence<N...>)
      {
        return tuple<std::tuple_element_t<N + I0, tuple>...> {(*this)[index<N + I0>]...};
      }
      (std::make_index_sequence<sizeof...(Ts) - I0>());
    }

    //==============================================================================================
    // Split a tuple into two tuples based on an index
    //==============================================================================================
    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts))
        [[nodiscard]] constexpr auto split(index_t<I0> const &) const noexcept;

    template<std::size_t I0>
    requires(I0 <= sizeof...(Ts)) [[nodiscard]] constexpr auto split(index_t<I0> const &) noexcept;

    //==============================================================================================
    // Informations on tuple
    //==============================================================================================
    [[nodiscard]] static constexpr auto size() noexcept { return sizeof...(Ts); }
    [[nodiscard]] static constexpr bool empty() noexcept { return sizeof...(Ts) == 0; }

    //==============================================================================================
    // Conversion
    //==============================================================================================
    template<typename... Us>
    requires(     detail::piecewise_convertible<tuple,tuple<Us...>>
              &&  (sizeof...(Us) == sizeof...(Ts))
              &&  (!std::same_as<Ts,Us> && ...)
            )
    [[nodiscard]] inline constexpr auto cast() const
    {
      return apply([](auto &&...elems) { return tuple<Us...>{ static_cast<Us>(elems)...}; }, *this);
    }

    //==============================================================================================
    // Assignment
    //==============================================================================================
    template<typename... Us>
    requires(detail::piecewise_convertible<tuple, tuple<Us...>>) constexpr tuple &
    operator=(tuple<Us...> const &other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((detail::get_leaf<I>(impl) = detail::get_leaf<I>(other.impl)), ...);
      }
      (std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    template<typename... Us>
    requires(detail::piecewise_convertible<tuple, tuple<Us...>>) constexpr tuple &
    operator=(tuple<Us...> &&other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        ((detail::get_leaf<I>(impl) = detail::get_leaf<I>(KUMI_FWD(other).impl)), ...);
      }
      (std::make_index_sequence<sizeof...(Ts)>());

      return *this;
    }

    //==============================================================================================
    // Comparison operators
    //==============================================================================================
    template<sized_product_type<sizeof...(Ts)> Other>
    friend constexpr bool operator==(tuple const &self, Other const &other) noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return ((detail::get_leaf<I>(self.impl) == detail::get_leaf<I>(other.impl)) && ...);
      }
      (std::make_index_sequence<sizeof...(Ts)>());
    }

    template<sized_product_type<sizeof...(Ts)> Other>
    friend constexpr bool operator!=(tuple const &self, Other const &other) noexcept
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        return ((detail::get_leaf<I>(self.impl) != detail::get_leaf<I>(other.impl)) || ...);
      }
      (std::make_index_sequence<sizeof...(Ts)>());
    }

    //==============================================================================================
    // Stream interaction
    //==============================================================================================
    template<typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &os,
                                                         tuple const &t) noexcept
    {
      os << "( ";
      kumi::for_each([&os](auto const &e) { os << e << " "; }, t);
      os << ")";

      return os;
    }
  };

  //================================================================================================
  // CTAD and other helpers
  //================================================================================================
  template<typename... Ts> tuple(Ts &&...) -> tuple<std::unwrap_ref_decay_t<Ts>...>;

  template<typename... Ts> [[nodiscard]] constexpr tuple<Ts &...> tie(Ts &...ts) { return {ts...}; }

  template<typename... Ts> [[nodiscard]] constexpr tuple<Ts &&...> forward_as_tuple(Ts &&...ts)
  {
    return {KUMI_FWD(ts)...};
  }

  template<typename... Ts>
  [[nodiscard]] constexpr tuple<std::unwrap_ref_decay_t<Ts>...> make_tuple(Ts &&...ts)
  {
    return {KUMI_FWD(ts)...};
  }

  template<typename... Ts> template<std::size_t I0>
  requires(I0 <= sizeof...(Ts))
      [[nodiscard]] constexpr auto tuple<Ts...>::split(index_t<I0> const &) const noexcept
  {
    return kumi::make_tuple(extract(index<0>, index<I0>), extract(index<I0>));
  }

  template<typename... Ts> template<std::size_t I0>
  requires(I0 <= sizeof...(Ts))
      [[nodiscard]] constexpr auto tuple<Ts...>::split(index_t<I0> const &) noexcept
  {
    return kumi::make_tuple(extract(index<0>, index<I0>), extract(index<I0>));
  }

  //================================================================================================
  // Conversions to arbitrary types
  //================================================================================================
  template<typename Type, typename... Ts>
  requires( !product_type<Type> && detail::implicit_constructible<Type, Ts...> )
  [[nodiscard]] constexpr auto tuple_cast(tuple<Ts...> const& t)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return Type{get<I>(t)...};
    }
    (std::make_index_sequence<sizeof...(Ts)>());
  }

  //================================================================================================
  // Access
  //================================================================================================
  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) [[nodiscard]] constexpr decltype(auto) get(tuple<Ts...> &arg) noexcept
  {
    return arg[index<I>];
  }

  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) [[nodiscard]] constexpr decltype(auto)
      get(tuple<Ts...> &&arg) noexcept
  {
    return static_cast<tuple<Ts...> &&>(arg)[index<I>];
  }

  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) [[nodiscard]] constexpr decltype(auto)
      get(tuple<Ts...> const &arg) noexcept
  {
    return arg[index<I>];
  }

  template<std::size_t I, typename... Ts>
  requires(I < sizeof...(Ts)) [[nodiscard]] constexpr decltype(auto)
      get(tuple<Ts...> const &&arg) noexcept
  {
    return static_cast<tuple<Ts...> const &&>(arg)[index<I>];
  }

  //================================================================================================
  // Construct the tuple made of the application of f to elements of each tuples
  //================================================================================================
  template<typename... Ts, typename Function, sized_product_type<sizeof...(Ts)>... Tuples>
  constexpr auto map(Function f, tuple<Ts...> const &t0, Tuples const &...others)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      auto call = [&]<std::size_t N>(index_t<N>, auto const &...args)
      { return f(detail::get_leaf<N>(args.impl)...); };

      return make_tuple(call(index<I>, t0, others...)...);
    }
    (std::make_index_sequence<sizeof...(Ts)>());
  }

  //================================================================================================
  // Generalized sums
  //================================================================================================
  template<typename Function, product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto fold_left(Function f, Tuple const &t, Value init)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return (detail::foldable {f, detail::get_leaf<I>(t.impl)} >> ...
              >> detail::foldable {f, init})
          .value;
    }
    (std::make_index_sequence<Tuple::size()>());
  }

  template<typename Function, product_type Tuple, typename Value>
  [[nodiscard]] constexpr auto fold_right(Function f, Tuple const &t, Value init)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      return (detail::foldable {f, init} << ...
                                         << detail::foldable {f, detail::get_leaf<I>(t.impl)})
          .value;
    }
    (std::make_index_sequence<Tuple::size()>());
  }

  //================================================================================================
  // Concatenates tuples
  //================================================================================================
  template<typename... Ts, typename... Us>
  [[nodiscard]] constexpr auto cat(tuple<Ts...> const &ts, tuple<Us...> const &us)
  {
    return [&]<std::size_t... TI, std::size_t... UI>(std::index_sequence<TI...>,
                                                     std::index_sequence<UI...>)
    {
      return tuple<Ts..., Us...> {get<TI>(ts)..., get<UI>(us)...};
    }
    (std::index_sequence_for<Ts...> {}, std::index_sequence_for<Us...> {});
  }

  template<typename... Ts, product_type... Tuples>
  [[nodiscard]] constexpr auto cat(tuple<Ts...> const &ts, Tuples const &...us)
  {
    auto const cc = [](auto const &a, auto const &b) { return cat(a, b); };
    return (detail::foldable {cc, ts} << ... << detail::foldable {cc, us}).value;
  }

  template<product_type T1, product_type T2>
  [[nodiscard]] constexpr auto operator|(T1 &&t1, T2 &&t2)
  {
    return kumi::cat(KUMI_FWD(t1), KUMI_FWD(t2));
  }

  //================================================================================================
  // Flatten nested tuples : one layer at a time or recursively
  //================================================================================================
  template<typename... Ts> [[nodiscard]] constexpr auto flatten(tuple<Ts...> const &ts)
  {
    return kumi::fold_right(
        []<typename M>(auto acc, M const &m)
        {
          if constexpr( product_type<M> )
            return cat(acc, m);
          else
            return cat(acc, kumi::tuple {m});
        },
        ts,
        kumi::tuple {});
  }

  template<typename... Ts> [[nodiscard]] constexpr auto flatten_all(tuple<Ts...> const &ts)
  {
    return kumi::fold_right(
        []<typename M>(auto acc, M const &m)
        {
          if constexpr( product_type<M> )
            return cat(acc, flatten(m));
          else
            return cat(acc, kumi::tuple {m});
        },
        ts,
        kumi::tuple {});
  }

  //================================================================================================
  // Zip multiple tuples contents
  //================================================================================================
  template<product_type T0, product_type... Ts>
  requires((std::remove_cvref_t<T0>::size() == std::remove_cvref_t<Ts>::size()) && ...)
      [[nodiscard]] constexpr auto zip(T0 &&t0, Ts &&...tuples)
  {
    return map(
        []<typename... Ms>(Ms && ...ms) { return make_tuple(std::forward<Ms>(ms)...); },
        std::forward<T0>(t0),
        std::forward<Ts>(tuples)...);
  }

  //================================================================================================
  // Transpose a tuple of tuples
  //================================================================================================
  template<typename T0, typename... Ts>
  [[nodiscard]] constexpr auto transpose(tuple<T0, Ts...> const &t)
  {
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
      constexpr auto uz = []<typename N>(N const &, auto const &u)
      { return apply([](auto const &...m) { return make_tuple(get<N::value>(m)...); }, u); };

      return make_tuple(uz(index_t<I> {}, t)...);
    }
    (std::make_index_sequence<T0::size()>());
  }

  //================================================================================================
  // Reorder elements of a tuple
  //================================================================================================
  template<std::size_t... Idx, product_type Tuple>
  requires((Idx < std::remove_cvref_t<Tuple>::size()) && ...)
      [[nodiscard]] constexpr auto reorder(Tuple &&t)
  {
    return make_tuple(KUMI_FWD(t)[index<Idx>]...);
  }
}

//==================================================================================================
// Structured binding adaptation
//==================================================================================================
namespace std
{
  template<std::size_t I, typename Head, typename... Tail>
  struct tuple_element<I, kumi::tuple<Head, Tail...>> : tuple_element<I - 1, kumi::tuple<Tail...>>
  {
  };

  template<std::size_t I, typename... Ts> struct tuple_element<I, kumi::tuple<Ts...> const>
  {
    using type = typename tuple_element<I, kumi::tuple<Ts...>>::type const;
  };

  template<typename Head, typename... Tail> struct tuple_element<0, kumi::tuple<Head, Tail...>>
  {
    using type = Head;
  };

  template<typename... Ts>
  struct tuple_size<kumi::tuple<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)>
  {
  };
}

#undef KUMI_FWD
