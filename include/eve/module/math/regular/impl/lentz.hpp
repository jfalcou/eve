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
  struct is_pair : std::false_type{};

  template <typename T, typename U>
  struct is_pair<kumi::tuple<T,U>> : std::true_type{};

  //
  // lentz_b
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

  template <typename Gen, typename U, callable_options O>
  EVE_FORCEINLINE constexpr auto lentz_b_(EVE_REQUIRES(cpu_), O const &, Gen g, const U& eps, size_t max_terms)
    noexcept
  {
    using eve::abs;
    auto v = g();
    constexpr auto pure_pair = is_pair<decltype(v)>::value;
    using tmp_t = decltype([v](){ if constexpr(pure_pair) return get<0>(v); else  return v;}());
    using r_t = std::decay_t<tmp_t>;
    using u_t =   underlying_type_t<r_t>;
    u_t tiny = 16*smallestposval(as<u_t>()) ;
    u_t terminator(eps <= 0 ? eve::abs(eps)*eve::eps(as<u_t>()) : u_t(eps));
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
        C = fam(get<1>(v), get<0>(v), rec[pedantic2](C));
      }
      else
      {
        D = v+D;
        C = v+rec[pedantic2](C);
      }
      D = if_else(is_eqz(D), tiny, D);
      C = if_else(is_eqz(C), tiny, C);
      D = rec[pedantic2](D);
      delta = C*D;
      f *= delta;
    } while (any(abs(dec(delta)) > terminator) && --counter);
    return f;
  }

  //
  // lentz_a
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

  template <typename Gen, typename U, callable_options O>
  EVE_FORCEINLINE auto lentz_a_(EVE_REQUIRES(cpu_), O const &, Gen g, const U& eps, size_t max_terms)  noexcept
  {
    using eve::abs;
    auto v = g();
    constexpr auto pure_pair = is_pair<decltype(v)>::value;
    using tmp_t = decltype([v](){ if constexpr(pure_pair) return get<0>(v); else  return v;}());
    using r_t = std::decay_t<tmp_t>;
    using u_t =   underlying_type_t<r_t>;
    u_t tiny = 16*smallestposval(as<u_t>()) ;
    u_t terminator(eps <= 0 ? eve::abs(eps)*eve::eps(as<u_t>()) : u_t(eps));
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
        C = fam(get<1>(v), get<0>(v), rec[pedantic2](C));
      }
      else
      {
        D = v+D;
        C = v+rec[pedantic2](C);
      }
      D = if_else(is_eqz(D), tiny, D);
      C = if_else(is_eqz(C), tiny, C);
      D = rec[pedantic2](D);
      delta = C*D;
      f *= delta;
    } while (eve::any(abs(dec(delta)) > terminator) && --counter);
    return a0/f;
  }
}
