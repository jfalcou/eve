//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/newton_impl.hpp>

namespace eve::detail
{
//================================================================================================
//== Newton with iterators
//================================================================================================

template<value T0, std::input_iterator IT0, std::input_iterator IT1>
EVE_FORCEINLINE constexpr auto
newton_(EVE_SUPPORTS(cpu_), T0 xx, IT0 const& firstc, IT0 const& lastc, IT1 const& firstn) noexcept
    requires((compatible_values<T0, typename std::iterator_traits<IT0>::value_type>)&&(
        compatible_values<T0, typename std::iterator_traits<IT1>::value_type>))
{
  return detail::newton_impl(regular_type(), xx, firstc, lastc, firstn);
}

//================================================================================================
//== Newton with ranges
//================================================================================================
template<value T0, range R1, range R2>
EVE_FORCEINLINE constexpr auto
newton_(EVE_SUPPORTS(cpu_), T0 xx, R1 const& rc, R2 const& rn) noexcept requires(
    compatible_values<
        T0,
        typename R1::
            value_type> && (!simd_value<R1>)&&compatible_values<T0, typename R2::value_type> && (!simd_value<R2>))
{
  return detail::newton_impl(regular_type(), xx, rc, rn);
}

namespace pipo{
template<kumi::product_type Tuple>
void print(const char * s, std::ostream& os, Tuple const& t)
{
  kumi::apply
  (
    [&os, s](auto const&... args)
    {
      os << s << " = [";
      std::size_t n{0};
      ((os << args << (++n != kumi::size<Tuple>::value ? ", " : "")), ...);
      os << ']';
    }, t
  );

  os << '\n';
}
}
//================================================================================================
//== Newton with tuples
//================================================================================================
template<value T0, kumi::product_type Coefs, kumi::product_type Nodes>
EVE_FORCEINLINE constexpr auto
newton_(EVE_SUPPORTS(cpu_), T0 xx, Coefs const& cs, Nodes const& ns) noexcept
{
  EVE_ASSERT((kumi::size_v<Coefs> == 0 && kumi::size_v<Nodes> == 0)|| (kumi::size_v<Coefs> ==  kumi::size_v<Nodes>+1), "nodes andcoefs have incompatible sizes");
  auto lambda = [](auto... m) { return (m + ...); };
  using func_t = decltype(lambda);
  using t_t = kumi::tuple<T0>;
  using cat_t  = decltype(kumi::flatten(kumi::cat(cs, ns, t_t())));
  using r_t = kumi::result::apply_t<func_t, cat_t>;
  if constexpr(kumi::size_v<Coefs> == 0) return zero(as<r_t>());
  else if constexpr(kumi::size_v<Coefs> == 1) return r_t(get<0>(cs));
  else
  {
    r_t that = r_t(get<0>(cs));
    auto ans = kumi::zip(kumi::pop_front(cs), ns);
    auto compute = [&](auto ... args){
      auto doit = [&](auto an){
        auto [a, n] = an;
        that =  fma(xx-n, that, a);
      };
      ((doit(args), ...));
      return that;
    };
    return kumi::apply(compute, ans);
  }
}

template<decorator D, value T0, kumi::product_type Coefs, kumi::product_type Nodes>
EVE_FORCEINLINE constexpr auto
newton_(EVE_SUPPORTS(cpu_), D const& d, T0 xx, Coefs const& cs, Nodes const& ns) noexcept
{
  auto lambda = [](auto... m) { return (m + ...); };
  using func_t = decltype(lambda);
  using t_t = kumi::tuple<T0>;
  using cat_t  = decltype(kumi::flatten(kumi::cat(cs, ns, t_t())));
  using r_t = kumi::result::apply_t<func_t, cat_t>;
  if constexpr(kumi::size_v<Coefs> == 0) return zero(as<r_t>());
  else if constexpr(kumi::size_v<Coefs> == 1) return r_t(get<0>(cs));
  else
  {
    r_t that = r_t(get<0>(cs));
    auto ans = kumi::zip(kumi::pop_front(cs), ns);
    auto compute = [&](auto ... args){
      auto doit = [&](auto an){
        auto [a, n] = an;
        that =  d(fma)(xx-n, that, a);
      };
      ((doit(args), ...));
      return that;
    };
    return kumi::apply(compute, ans);
  }
}
}
