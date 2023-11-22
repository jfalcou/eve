//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{

  template <typename T>
  struct is_pair : public std::false_type{};

  template <typename T, typename U>
  struct is_pair<kumi::tuple<T,U>> : public std::true_type{};

  template <typename T>
  concept addable = requires(T a, T b, T c){c = a+b; };

 template <typename Gen>
  struct fraction_traits_simple
  {
    using result_type = typename Gen::result_type;
    using  value_type = typename Gen::result_type;

    static result_type a(const value_type&) noexcept
    {
      return result_type(1);
    }
    static result_type b(const value_type& v) noexcept
    {
      return v;
    }
  };

  template <typename Gen>
  struct fraction_traits_pair
  {
    using  value_type = typename Gen::result_type;
    using result_type = kumi::element_t<0, value_type>;

    static auto a(const value_type& v) noexcept
    {
      return get<0>(v);
    }
    static auto b(const value_type& v) noexcept
    {
      return get<1>(v);
    }
  };

  template <typename Gen>
  struct fraction_traits
    : public std::conditional<
    is_pair<typename Gen::result_type>::value,
    fraction_traits_pair<Gen>,
    fraction_traits_simple<Gen>>::type
  {};

//   template <typename T>
//   struct tiny_value
//   {
//     using u_t = eve::underlying_type<T>;
//     static T get() { return 16*eve::smallestposval(as<T>()); }
//   };

  //
  // continued_fraction_b
  // Evaluates:
  //
  //               a1
  //     b0 + -----------
  //                   a2
  //          b1 + -----------
  //                        a3
  //               b2 + ----------
  //                       ...
  //
  // Note that the first a0 returned by generator Gen is discarded.
  //

  template <typename Gen, typename U>
  EVE_FORCEINLINE constexpr auto lentz_b_(EVE_SUPPORTS(cpu_), Gen g, const U& eps, size_t max_terms)
    noexcept
  {
    using eve::abs;
    auto v = g();
    constexpr auto pure_pair = is_pair<decltype(v)>::value && !addable<decltype(v)>;
    using tmp_t = decltype([v](){ if constexpr(pure_pair) return get<0>(v); else  return v;}());
    using r_t = std::decay_t<tmp_t>;
    using u_t =   underlying_type_t<r_t>;
    u_t tiny = 16*smallestposval(as<u_t>()) ;
    u_t terminator(eps <= 0 ? 16*eve::eps(as<u_t>()) : u_t(eps));
    size_t counter(max_terms);

    r_t f{};
    if constexpr(pure_pair) f = get<1>(v); else f = v;
    f = if_else(is_eqz(f), tiny, f);
    r_t C = f;
    r_t D{0};
    r_t delta{};

    do{
      v = g();
      if constexpr(pure_pair)
      {
        D = fam(get<1>(v), get<0>(v), D);
        C = fam(get<1>(v), get<0>(v), rec(C));
      }
      else
      {
        D = v+D;
        C = v+rec(C);
      }
      D = if_else(is_eqz(D), tiny, D);
      C = if_else(is_eqz(C), tiny, C);
      D = rec(D);
      delta = C*D;
      f *= delta;
    } while (any(abs(dec(delta)) > terminator) && --counter);
    return f;
  }

  //
  // continued_fraction_a
  // Evaluates:
  //
  //            a0
  //      ------------
  //                a1
  //      b0 + -----------
  //                    a2
  //           b1 + ----------
  //                        a3
  //                 b2 + -------
  //                        ...
  //
  // Note that the first a0 and b0 returned by generator Gen are both used.
  //

  template <typename Gen, typename U>
  EVE_FORCEINLINE auto lentz_a_(EVE_SUPPORTS(cpu_), Gen g, const U& eps, size_t max_terms)  noexcept
  {
    using eve::abs;
    auto v = g();
    constexpr auto pure_pair = is_pair<decltype(v)>::value && !addable<decltype(v)>;
    using tmp_t = decltype([v](){ if constexpr(pure_pair) return get<0>(v); else  return v;}());
    using r_t = std::decay_t<tmp_t>;
    using u_t =   underlying_type_t<r_t>;
    u_t tiny = 16*smallestposval(as<u_t>()) ;
    u_t terminator(eps <= 0 ? 16*eve::eps(as<u_t>()) : u_t(eps));
    size_t counter(max_terms);

    r_t f{};
    if constexpr(pure_pair) f = get<1>(v); else f = v;
    f = if_else(is_eqz(f), tiny, f);
    r_t a0{};
    if constexpr(pure_pair) a0 = get<0>(v); else a0 = one(as<r_t>());
    a0 = if_else(is_eqz(a0), tiny, a0);
    auto C = f;
    r_t  D{0};
    auto delta(D);
    do{
      v = g();
      if constexpr(pure_pair)
      {
        D = fam(get<1>(v), get<0>(v), D);
        C = fam(get<1>(v), get<0>(v), rec(C));
      }
      else
      {
        D = v+D;
        C = v+rec(C);
      }
      D = if_else(is_eqz(D), tiny, D);
      C = if_else(is_eqz(C), tiny, C);
      D = rec(D);
      delta = C*D;
      f *= delta;
    } while (eve::any(abs(dec(delta)) > terminator) && --counter);
    return a0/f;
  }
}
