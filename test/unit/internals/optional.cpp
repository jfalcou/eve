//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
// Tests heavily inspired by libc++ (LLVM Project, Apache-2.0 WITH LLVM-exception).

#include "test.hpp"

#include <eve/detail/optional.hpp>

#include <array>
#include <compare>
#include <iostream>
#include <limits>
#include <optional>
#include <utility>

#include <source_location>
#include <type_traits>

namespace
{
using eve::_::nullopt;
using eve::_::optional;

inline void
report_failure(std::source_location where)
{
  std::cerr << where.file_name() << ':' << where.line() << ": check failed\n";
}

struct checks
{
  bool ok = true;

  constexpr void operator()(bool b, std::source_location where = std::source_location::current())
  {
    if( !b )
    {
      report_failure(where);
      ok = false;
    }
  }
};

struct nontrivial
{
  int v;

  constexpr nontrivial(int x) : v(x) {}
  constexpr nontrivial(nontrivial const& o) : v(o.v) {}
  constexpr nontrivial(nontrivial&& o) noexcept : v(o.v) {}
  constexpr nontrivial& operator=(nontrivial const& o)
  {
    v = o.v;
    return *this;
  }
  constexpr nontrivial& operator=(nontrivial&& o) noexcept
  {
    v = o.v;
    return *this;
  }
  constexpr ~nontrivial() {}

  constexpr auto operator<=>(nontrivial const&) const = default;
};

struct with_default
{
  int v = 7;

  constexpr with_default() = default;
  constexpr with_default(int x) : v(x) {}

  constexpr auto operator<=>(with_default const&) const = default;
};

struct int_tombstone
{
  static constexpr int value = std::numeric_limits<int>::min();
};

struct array_tombstone
{
  static constexpr std::array<long, 2> value {-1, -1};
};

struct plain_int
{
  using type    = optional<int>;
  using storage = eve::_::optional_plain_storage<int>;
  using other   = optional<int, int_tombstone>;
  static constexpr int value(int i) { return i; }
};

struct tombstone_int
{
  using type    = optional<int, int_tombstone>;
  using storage = eve::_::optional_tombstone_storage<int, int_tombstone>;
  using other   = optional<int>;
  static constexpr int value(int i) { return i; }
};

struct plain_array
{
  using type    = optional<std::array<long, 2>>;
  using storage = eve::_::optional_plain_storage<std::array<long, 2>>;
  using other   = optional<std::array<long, 2>, array_tombstone>;
  static constexpr std::array<long, 2> value(int i) { return {i, i + 1}; }
};

struct tombstone_array
{
  using type    = optional<std::array<long, 2>, array_tombstone>;
  using storage = eve::_::optional_tombstone_storage<std::array<long, 2>, array_tombstone>;
  using other   = optional<std::array<long, 2>>;
  static constexpr std::array<long, 2> value(int i) { return {i, i + 1}; }
};

struct union_nontrivial
{
  using type    = optional<nontrivial>;
  using storage = eve::_::optional_union_storage<nontrivial>;
  static constexpr nontrivial value(int i) { return nontrivial {i}; }
};

struct union_with_default
{
  using type    = optional<with_default>;
  using storage = eve::_::optional_union_storage<with_default>;
  static constexpr with_default value(int i) { return with_default {i}; }
};

using configs = tts::types<plain_int,
                           tombstone_int,
                           plain_array,
                           tombstone_array,
                           union_nontrivial,
                           union_with_default>;

template<typename C> using opt_t = typename C::type;
template<typename C> using val_t = typename C::type::value_type;

template<typename C>
constexpr bool
storage_selection()
{
  return std::is_base_of_v<typename C::storage, opt_t<C>>;
}

template<typename C>
constexpr bool
types()
{
  using O = opt_t<C>;
  using T = val_t<C>;
  checks expect;
  expect(std::is_same_v<decltype(*std::declval<O&>()), T&>);
  expect(std::is_same_v<decltype(*std::declval<O const&>()), T const&>);
  expect(std::is_same_v<decltype(*std::declval<O&&>()), T&&>);
  expect(std::is_same_v<decltype(*std::declval<O const&&>()), T const&&>);
  expect(std::is_same_v<decltype(std::declval<O&>().value()), T&>);
  expect(std::is_same_v<decltype(std::declval<O&&>().value()), T&&>);
  expect(std::is_same_v<decltype(std::declval<O&>().operator->()), T *>);
  expect(std::is_same_v<decltype(std::declval<O const&>().operator->()), T const *>);
  expect(noexcept(std::declval<O&>().reset()));
  expect(noexcept(std::declval<O&>().has_value()));
  expect(std::is_nothrow_constructible_v<O>);
  expect(std::is_nothrow_constructible_v<O, eve::_::nullopt_t>);
  expect(std::is_nothrow_constructible_v<O, std::nullopt_t>);
  expect(!std::is_convertible_v<O, bool>);
  expect(std::is_constructible_v<bool, O>);
  return expect.ok;
}

template<typename C>
constexpr bool
default_and_none_ctor()
{
  checks expect;
  {
    opt_t<C> o;
    expect(!o.has_value());
    expect(!static_cast<bool>(o));
  }
  {
    opt_t<C> o {nullopt};
    expect(!o.has_value());
  }
  {
    opt_t<C> o {std::nullopt};
    expect(!o.has_value());
  }
  {
    opt_t<C> o = {};
    expect(!o.has_value());
  }
  return expect.ok;
}

template<typename C>
constexpr bool
value_ctor()
{
  checks expect;
  {
    val_t<C> const v = C::value(1);
    opt_t<C>       o(v);
    expect(o.has_value());
    expect(*o == C::value(1));
  }
  {
    opt_t<C> o(C::value(2));
    expect(o.has_value());
    expect(*o == C::value(2));
  }
  {
    opt_t<C> o = C::value(3);
    expect(*o == C::value(3));
  }
  {
    opt_t<C> o(std::in_place, C::value(4));
    expect(*o == C::value(4));
  }
  return expect.ok;
}

template<typename C>
constexpr bool
copy_and_move_ctor()
{
  checks expect;
  {
    opt_t<C> const a;
    opt_t<C>       b(a);
    expect(!b.has_value());
  }
  {
    opt_t<C> const a(C::value(1));
    opt_t<C>       b(a);
    expect(b.has_value() && *b == C::value(1));
    expect(a.has_value() && *a == C::value(1));
  }
  {
    opt_t<C> a;
    opt_t<C> b(std::move(a));
    expect(!b.has_value());
  }
  {
    opt_t<C> a(C::value(2));
    opt_t<C> b(std::move(a));
    expect(b.has_value() && *b == C::value(2));
  }
  return expect.ok;
}

template<typename C>
constexpr bool
converting_ctor()
{
  checks expect;
  if constexpr( requires { typename C::other; } )
  {
    using other = typename C::other;
    {
      other const a;
      opt_t<C>    b(a);
      expect(!b.has_value());
    }
    {
      other const a(C::value(1));
      opt_t<C>    b(a);
      expect(b.has_value() && *b == C::value(1));
    }
    {
      other    a(C::value(2));
      opt_t<C> b(std::move(a));
      expect(b.has_value() && *b == C::value(2));
    }
    {
      other    a;
      opt_t<C> b(std::move(a));
      expect(!b.has_value());
    }
  }
  return expect.ok;
}

template<typename C>
constexpr bool
assign_none()
{
  checks expect;
  {
    opt_t<C> o(C::value(1));
    o = nullopt;
    expect(!o.has_value());
  }
  {
    opt_t<C> o(C::value(1));
    o = std::nullopt;
    expect(!o.has_value());
  }
  {
    opt_t<C> o;
    o = nullopt;
    expect(!o.has_value());
  }
  {
    opt_t<C> o(C::value(1));
    o = {};
    expect(!o.has_value());
  }
  return expect.ok;
}

template<typename C>
constexpr bool
assign_value()
{
  checks expect;
  {
    opt_t<C> o;
    o = C::value(1);
    expect(o.has_value() && *o == C::value(1));
  }
  {
    opt_t<C> o(C::value(1));
    o = C::value(2);
    expect(o.has_value() && *o == C::value(2));
  }
  {
    opt_t<C>       o;
    val_t<C> const v = C::value(3);
    o                = v;
    expect(*o == C::value(3));
  }
  return expect.ok;
}

template<typename C>
constexpr bool
assign_copy_and_move()
{
  checks     expect;
  auto const all = [&](auto assign)
  {
    for( int lhs = 0; lhs != 2; ++lhs )
      for( int rhs = 0; rhs != 2; ++rhs )
      {
        opt_t<C> a = lhs ? opt_t<C>(C::value(1)) : opt_t<C>();
        opt_t<C> b = rhs ? opt_t<C>(C::value(2)) : opt_t<C>();
        assign(a, b);
        expect(a.has_value() == static_cast<bool>(rhs));
        if( rhs ) expect(*a == C::value(2));
      }
  };
  all([](opt_t<C>& a, opt_t<C>& b) { a = b; });
  all([](opt_t<C>& a, opt_t<C>& b) { a = std::move(b); });
  all([](opt_t<C>& a, opt_t<C> const& b) { a = b; });
  return expect.ok;
}

template<typename C>
constexpr bool
assign_converting()
{
  checks expect;
  if constexpr( requires { typename C::other; } )
  {
    using other = typename C::other;
    for( int lhs = 0; lhs != 2; ++lhs )
      for( int rhs = 0; rhs != 2; ++rhs )
      {
        opt_t<C> a = lhs ? opt_t<C>(C::value(1)) : opt_t<C>();
        other    b = rhs ? other(C::value(2)) : other();
        a          = b;
        expect(a.has_value() == static_cast<bool>(rhs));
        if( rhs ) expect(*a == C::value(2));

        opt_t<C> c = lhs ? opt_t<C>(C::value(1)) : opt_t<C>();
        c          = std::move(b);
        expect(c.has_value() == static_cast<bool>(rhs));
        if( rhs ) expect(*c == C::value(2));
      }
  }
  return expect.ok;
}

template<typename C>
constexpr bool
emplace()
{
  checks expect;
  {
    opt_t<C>  o;
    val_t<C>& r = o.emplace(C::value(1));
    expect(o.has_value() && *o == C::value(1));
    expect(&r == &*o);
  }
  {
    opt_t<C> o(C::value(1));
    o.emplace(C::value(2));
    expect(o.has_value() && *o == C::value(2));
  }
  return expect.ok;
}

template<typename C>
constexpr bool
reset()
{
  checks expect;
  {
    opt_t<C> o;
    o.reset();
    expect(!o.has_value());
  }
  {
    opt_t<C> o(C::value(1));
    o.reset();
    expect(!o.has_value());
    o = C::value(2);
    expect(o.has_value() && *o == C::value(2));
  }
  return expect.ok;
}

template<typename C>
constexpr bool
swap()
{
  checks     expect;
  auto const all = [&](auto do_swap)
  {
    for( int lhs = 0; lhs != 2; ++lhs )
      for( int rhs = 0; rhs != 2; ++rhs )
      {
        opt_t<C> a = lhs ? opt_t<C>(C::value(1)) : opt_t<C>();
        opt_t<C> b = rhs ? opt_t<C>(C::value(2)) : opt_t<C>();
        do_swap(a, b);
        expect(a.has_value() == static_cast<bool>(rhs));
        expect(b.has_value() == static_cast<bool>(lhs));
        if( rhs ) expect(*a == C::value(2));
        if( lhs ) expect(*b == C::value(1));
      }
  };
  all([](opt_t<C>& a, opt_t<C>& b) { a.swap(b); });
  all([](opt_t<C>& a, opt_t<C>& b) { swap(a, b); });
  return expect.ok;
}

template<typename C>
constexpr bool
observers()
{
  checks          expect;
  opt_t<C>        o(C::value(1));
  opt_t<C> const& c = o;
  expect(*o == C::value(1));
  expect(*c == C::value(1));
  expect(*std::move(o) == C::value(1));
  expect(o.value() == C::value(1));
  expect(c.value() == C::value(1));
  expect(o.operator->() == &*o);
  expect(c.operator->() == &*c);
  expect(o.has_value());
  expect(static_cast<bool>(o));
  return expect.ok;
}

template<typename C>
constexpr bool
value_or()
{
  checks expect;
  {
    opt_t<C> const o;
    expect(o.value_or(C::value(2)) == C::value(2));
  }
  {
    opt_t<C> const o(C::value(1));
    expect(o.value_or(C::value(2)) == C::value(1));
  }
  {
    expect(opt_t<C>().value_or(C::value(2)) == C::value(2));
    expect(opt_t<C>(C::value(1)).value_or(C::value(2)) == C::value(1));
  }
  return expect.ok;
}

template<typename C>
constexpr bool
relops()
{
  checks         expect;
  opt_t<C> const e;
  opt_t<C> const e2;
  opt_t<C> const one(C::value(1));
  opt_t<C> const one2(C::value(1));
  opt_t<C> const two(C::value(2));

  expect(e == e2);
  expect(one == one2);
  expect(!(e == one));
  expect(!(one == two));

  expect(!(e != e2));
  expect(e != one);
  expect(one != two);

  expect(e < one);
  expect(!(one < e));
  expect(!(e < e2));
  expect(one < two);
  expect(!(two < one));

  expect(e <= e2);
  expect(e <= one);
  expect(!(one <= e));
  expect(one <= one2);
  expect(one <= two);

  expect(one > e);
  expect(!(e > one));
  expect(!(e > e2));
  expect(two > one);

  expect(e >= e2);
  expect(one >= e);
  expect(!(e >= one));
  expect(two >= one);
  expect(one >= one2);

  expect((e <=> e2) == 0);
  expect((e <=> one) < 0);
  expect((one <=> e) > 0);
  expect((one <=> two) < 0);
  expect((one <=> one2) == 0);
  return expect.ok;
}

template<typename C>
constexpr bool
relops_converting()
{
  checks expect;
  if constexpr( requires { typename C::other; } )
  {
    using other = typename C::other;
    opt_t<C> const e;
    opt_t<C> const one(C::value(1));
    other const    oe;
    other const    otwo(C::value(2));

    expect(e == oe);
    expect(e < otwo);
    expect(one < otwo);
    expect(one != otwo);
    expect((one <=> otwo) < 0);
    expect((one <=> oe) > 0);
  }
  return expect.ok;
}

template<typename C>
constexpr bool
nullops()
{
  checks         expect;
  opt_t<C> const e;
  opt_t<C> const one(C::value(1));

  auto const check = [&](auto n)
  {
    expect(e == n);
    expect(n == e);
    expect(!(one == n));
    expect(!(n == one));

    expect(!(e != n));
    expect(one != n);
    expect(n != one);

    expect(!(e < n));
    expect(!(n < e));
    expect(n < one);
    expect(!(one < n));

    expect(e <= n);
    expect(n <= e);
    expect(n <= one);
    expect(!(one <= n));

    expect(one > n);
    expect(!(n > one));
    expect(!(e > n));

    expect(e >= n);
    expect(one >= n);
    expect(!(n >= one));

    expect((e <=> n) == 0);
    expect((one <=> n) > 0);
    expect((n <=> one) < 0);
  };
  check(nullopt);
  check(std::nullopt);
  return expect.ok;
}

template<typename C>
constexpr bool
comp_with_t()
{
  checks         expect;
  opt_t<C> const e;
  opt_t<C> const one(C::value(1));
  val_t<C> const v1 = C::value(1);
  val_t<C> const v2 = C::value(2);

  expect(one == v1);
  expect(v1 == one);
  expect(!(e == v1));
  expect(!(v1 == e));

  expect(one != v2);
  expect(v2 != one);
  expect(e != v1);
  expect(v1 != e);

  expect(e < v1);
  expect(!(v1 < e));
  expect(one < v2);
  expect(!(v2 < one));

  expect(e <= v1);
  expect(one <= v1);
  expect(!(v2 <= one));
  expect(!(v1 <= e));

  expect(v1 > e);
  expect(v2 > one);
  expect(!(e > v1));

  expect(v1 >= e);
  expect(one >= v1);
  expect(!(e >= v1));

  expect((e <=> v1) < 0);
  expect((one <=> v1) == 0);
  expect((one <=> v2) < 0);
  expect((v2 <=> one) > 0);
  return expect.ok;
}

template<typename C>
constexpr bool
monadic()
{
  checks         expect;
  opt_t<C> const e;
  opt_t<C> const one(C::value(1));

  auto const twice = [](val_t<C> const& v) { return optional<int>(v == C::value(1) ? 2 : 0); };
  auto const nope  = [](val_t<C> const&) { return optional<int> {}; };

  expect(e.and_then(twice) == nullopt);
  expect(one.and_then(twice) == 2);
  expect(one.and_then(nope) == nullopt);
  expect(opt_t<C>(one).and_then(twice) == 2);

  auto const tag = [](val_t<C> const& v) { return v == C::value(1) ? 'a' : 'b'; };
  expect(std::is_same_v<decltype(one.transform(tag)), optional<char>>);
  expect(e.transform(tag) == nullopt);
  expect(one.transform(tag) == 'a');
  expect(opt_t<C>(one).transform(tag) == 'a');

  auto const fallback = [] { return opt_t<C>(C::value(2)); };
  expect(e.or_else(fallback) == C::value(2));
  expect(one.or_else(fallback) == C::value(1));
  expect(opt_t<C>().or_else(fallback) == C::value(2));
  expect(opt_t<C>(one).or_else(fallback) == C::value(1));
  return expect.ok;
}

template<typename C>
constexpr bool
make_optional_and_to_std()
{
  checks expect;
  {
    auto o = eve::_::make_optional(C::value(1));
    expect(std::is_same_v<decltype(o), optional<val_t<C>>>);
    expect(o == C::value(1));
  }
  {
    auto o = eve::_::make_optional<val_t<C>>(C::value(2));
    expect(o == C::value(2));
  }
  {
    opt_t<C> const e;
    opt_t<C> const one(C::value(1));
    expect(std::is_same_v<decltype(one.to_std()), std::optional<val_t<C>>>);
    expect(!e.to_std().has_value());
    expect(one.to_std() == C::value(1));
    expect(opt_t<C>(one).to_std() == C::value(1));
  }
  return expect.ok;
}

#define EVE_OPTIONAL_CASE(NAME)                                                                    \
  TTS_CASE_TPL("eve::_::optional - " #NAME, configs)                                               \
  <typename C>(tts::type<C>)                                                                       \
  {                                                                                                \
    TTS_CONSTEXPR_EXPECT(NAME<C>());                                                               \
    TTS_EXPECT(NAME<C>());                                                                         \
  };

EVE_OPTIONAL_CASE(storage_selection)
EVE_OPTIONAL_CASE(types)
EVE_OPTIONAL_CASE(default_and_none_ctor)
EVE_OPTIONAL_CASE(value_ctor)
EVE_OPTIONAL_CASE(copy_and_move_ctor)
EVE_OPTIONAL_CASE(converting_ctor)
EVE_OPTIONAL_CASE(assign_none)
EVE_OPTIONAL_CASE(assign_value)
EVE_OPTIONAL_CASE(assign_copy_and_move)
EVE_OPTIONAL_CASE(assign_converting)
EVE_OPTIONAL_CASE(emplace)
EVE_OPTIONAL_CASE(reset)
EVE_OPTIONAL_CASE(swap)
EVE_OPTIONAL_CASE(observers)
EVE_OPTIONAL_CASE(value_or)
EVE_OPTIONAL_CASE(relops)
EVE_OPTIONAL_CASE(relops_converting)
EVE_OPTIONAL_CASE(nullops)
EVE_OPTIONAL_CASE(comp_with_t)
EVE_OPTIONAL_CASE(monadic)
EVE_OPTIONAL_CASE(make_optional_and_to_std)

struct counted
{
  int *destroyed;

  constexpr explicit counted(int *d) : destroyed(d) {}
  constexpr counted(counted const& o) : destroyed(o.destroyed) {}
  constexpr counted& operator=(counted const& o)
  {
    destroyed = o.destroyed;
    return *this;
  }
  constexpr ~counted() { ++*destroyed; }
};

constexpr bool
destruction()
{
  checks expect;
  int    n = 0;
  {
    optional<counted> o;
  }
  expect(n == 0);
  {
    optional<counted> o(std::in_place, &n);
  }
  expect(n == 1);
  {
    optional<counted> o(std::in_place, &n);
    o.reset();
    expect(n == 2);
    o.reset();
    expect(n == 2);
    o.emplace(&n);
    o = nullopt;
    expect(n == 3);
    o.emplace(&n);
    o.emplace(&n);
    expect(n == 4);
  }
  expect(n == 5);
  return expect.ok;
}

TTS_CASE("eve::_::optional - destroys the value it holds")
{
  TTS_CONSTEXPR_EXPECT(destruction());
  TTS_EXPECT(destruction());
};

struct move_only
{
  int v;
  constexpr explicit move_only(int x) : v(x) {}
  move_only(move_only const&)                 = delete;
  move_only& operator=(move_only const&)      = delete;
  constexpr move_only(move_only&&)            = default;
  constexpr move_only& operator=(move_only&&) = default;
};

struct immovable
{
  int v;
  constexpr explicit immovable(int x) : v(x) {}
  immovable(immovable&&) = delete;
};

constexpr bool
special_members()
{
  checks expect;
  expect(!std::is_copy_constructible_v<optional<move_only>>);
  expect(!std::is_copy_assignable_v<optional<move_only>>);
  expect(std::is_move_constructible_v<optional<move_only>>);
  expect(std::is_move_assignable_v<optional<move_only>>);
  expect(!std::is_move_constructible_v<optional<immovable>>);

  optional<move_only> a(std::in_place, 1);
  optional<move_only> b(std::move(a));
  expect(b->v == 1);
  optional<move_only> c;
  c = std::move(b);
  expect(c->v == 1);

  optional<immovable> d(std::in_place, 3);
  expect(d->v == 3);

  auto const          make = [](int x) { return immovable {x}; };
  optional<int> const four(4);
  expect(std::is_same_v<decltype(four.transform(make)), optional<immovable>>);
  expect(four.transform(make)->v == 4);
  return expect.ok;
}

TTS_CASE("eve::_::optional - special members follow T")
{
  TTS_CONSTEXPR_EXPECT(special_members());
  TTS_EXPECT(special_members());
};

TTS_CASE("eve::_::optional - triviality follows T")
{
  TTS_CONSTEXPR_EXPECT(std::is_trivially_copyable_v<optional<int>>);
  TTS_CONSTEXPR_EXPECT((std::is_trivially_copyable_v<optional<int, int_tombstone>>));
  TTS_CONSTEXPR_EXPECT((std::is_trivially_copyable_v<optional<std::array<long, 2>>>));
  TTS_CONSTEXPR_EXPECT(std::is_trivially_copyable_v<optional<with_default>>);
  TTS_CONSTEXPR_EXPECT(std::is_trivially_destructible_v<optional<with_default>>);
  TTS_CONSTEXPR_EXPECT_NOT(std::is_trivially_copyable_v<optional<nontrivial>>);
  TTS_CONSTEXPR_EXPECT_NOT(std::is_trivially_destructible_v<optional<nontrivial>>);
};

TTS_CASE("eve::_::optional - a tombstone takes no extra space")
{
  TTS_CONSTEXPR_EXPECT((sizeof(optional<int, int_tombstone>) == sizeof(int)));
  TTS_CONSTEXPR_EXPECT(
      (sizeof(optional<std::array<long, 2>, array_tombstone>) == sizeof(std::array<long, 2>)));
};

constexpr bool
nullopt_is_below_every_value()
{
  checks                             expect;
  optional<int, int_tombstone> const lowest(std::numeric_limits<int>::min() + 1);
  expect(optional<int, int_tombstone> {} < lowest);
  expect(nullopt < lowest);
  return expect.ok;
}

TTS_CASE("eve::_::optional - nullopt is below every value, whatever the tombstone")
{
  TTS_CONSTEXPR_EXPECT(nullopt_is_below_every_value());
  TTS_EXPECT(nullopt_is_below_every_value());
};

template<typename F>
concept constant_evaluates = requires { typename std::bool_constant<(F {}(), true)>; };

struct store_value
{
  constexpr void operator()() const
  {
    optional<int, int_tombstone> o(5);
    o = 6;
    o.emplace(7);
  }
};

struct construct_tombstone
{
  constexpr void operator()() const { optional<int, int_tombstone> o(int_tombstone::value); }
};

struct assign_tombstone
{
  constexpr void operator()() const
  {
    optional<int, int_tombstone> o(5);
    o = int_tombstone::value;
  }
};

struct emplace_tombstone
{
  constexpr void operator()() const
  {
    optional<int, int_tombstone> o;
    o.emplace(int_tombstone::value);
  }
};

struct convert_tombstone
{
  constexpr void operator()() const
  {
    optional<int> const          p(int_tombstone::value);
    optional<int, int_tombstone> o(5);
    o = p;
  }
};

TTS_CASE("eve::_::optional - storing the tombstone asserts")
{
  TTS_CONSTEXPR_EXPECT(constant_evaluates<store_value>);
#if !defined(EVE_DISABLE_ASSERTS)
  TTS_CONSTEXPR_EXPECT_NOT(constant_evaluates<construct_tombstone>);
  TTS_CONSTEXPR_EXPECT_NOT(constant_evaluates<assign_tombstone>);
  TTS_CONSTEXPR_EXPECT_NOT(constant_evaluates<emplace_tombstone>);
  TTS_CONSTEXPR_EXPECT_NOT(constant_evaluates<convert_tombstone>);
#endif
};

struct explicit_from_int
{
  int v;
  constexpr explicit explicit_from_int(int x) : v(x) {}
};

TTS_CASE("eve::_::optional - conditionally explicit conversions")
{
  TTS_CONSTEXPR_EXPECT((std::is_convertible_v<int, optional<long>>));
  TTS_CONSTEXPR_EXPECT((std::is_convertible_v<optional<int>, optional<long>>));
  TTS_CONSTEXPR_EXPECT((std::is_convertible_v<optional<int> const&, optional<long>>));
  TTS_CONSTEXPR_EXPECT_NOT((std::is_convertible_v<int, optional<explicit_from_int>>));
  TTS_CONSTEXPR_EXPECT_NOT((std::is_convertible_v<optional<int>, optional<explicit_from_int>>));
  TTS_CONSTEXPR_EXPECT((std::is_constructible_v<optional<explicit_from_int>, int>));
  TTS_CONSTEXPR_EXPECT((std::is_constructible_v<optional<explicit_from_int>, optional<int>>));
  TTS_CONSTEXPR_EXPECT(eve::_::optional<explicit_from_int>(optional<int>(3))->v == 3);
};

constexpr bool
optional_of_bool()
{
  checks               expect;
  optional<int> const  e;
  optional<bool> const b(e);
  expect(!b.has_value());

  optional<int> const  zero(0);
  optional<bool> const z(zero);
  expect(z.has_value() && *z == false);
  return expect.ok;
}

TTS_CASE("eve::_::optional - optional<bool> converts from optional<U> by value")
{
  TTS_CONSTEXPR_EXPECT(optional_of_bool());
  TTS_EXPECT(optional_of_bool());
};

TTS_CASE("eve::_::optional - deduction guide")
{
  TTS_CONSTEXPR_EXPECT((std::is_same_v<decltype(optional(3)), optional<int>>));
  TTS_CONSTEXPR_EXPECT((std::is_same_v<decltype(optional(optional(3))), optional<int>>));
};
}
