//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/module/core/compress/detail/compress_callable.hpp>
#include <eve/module/core/regular/none.hpp>
#include <eve/module/core/regular/read.hpp>
#include <eve/module/core/regular/write.hpp>

namespace eve::detail
{

template<typename I, typename O> struct copy_by_one_checking_each_lambda_unsafe
{
  I& f;
  O& o;

  EVE_FORCEINLINE
  bool operator()(bool v)
  {
    eve::write(eve::read(f++), o);
    o += v;
    return false;
  }
};

template<typename... Args>
copy_by_one_checking_each_lambda_unsafe(Args...)
    -> copy_by_one_checking_each_lambda_unsafe<Args...>;

template<typename I, typename O> struct copy_by_one_checking_each_lambda_safe
{
  I& f;
  O& o;

  EVE_FORCEINLINE
  bool operator()(bool v)
  {
    I cur = f++;
    if( v ) { eve::write(eve::read(cur), o++); }
    return false;
  }
};

template<typename... Args>
copy_by_one_checking_each_lambda_safe(Args...) -> copy_by_one_checking_each_lambda_safe<Args...>;

template<typename I, typename O> struct copy_by_one_checking_each_lambda_checked
{
  I& f;
  O& o;
  O  limit;

  EVE_FORCEINLINE
  bool operator()(bool v)
  {
    I cur = f++;
    if( v )
    {
      if( o == limit ) return true;
      eve::write(eve::read(cur), o++);
    }
    return false;
  }
};

template<typename I, typename O>
copy_by_one_checking_each_lambda_checked(I, O, O)
    -> copy_by_one_checking_each_lambda_checked<I, O>;

template<typename M>
EVE_FORCEINLINE
bool
for_each_until_m(M m, auto op)
{
  if constexpr( M::size() == 1 ) return op(m.get(0));
  if constexpr( M::size() == 2 ) return op(m.get(0)) || op(m.get(1));
  if constexpr( M::size() == 4 )
  {
    return op(m.get(0)) || op(m.get(1)) || op(m.get(2)) || op(m.get(3));
  }
  if constexpr( M::size() > 4 )
  {
    static_assert(!logical_value<M>, "should be top bits");
    int i = 0;
    while( i != M::size() )
    {
      if( op(m.get(i)) ) return true;
      if( op(m.get(i + 1)) ) return true;
      if( op(m.get(i + 2)) ) return true;
      if( op(m.get(i + 3)) ) return true;
      i += 4;
    }
    return false;
  }
}

template<typename Settings, typename I, typename M, typename O>
EVE_FORCEINLINE auto
copy_by_one_checking_each(Settings settings, I f, M m, O o) -> O
{
  static_assert(std::same_as<typename Settings::cond_in_t, ignore_none_>);
  using OC = typename Settings::cond_out_t;

  if constexpr( OC::is_complete && Settings::is_safe )
  {
    for_each_until_m(m, copy_by_one_checking_each_lambda_safe {f, o});
  }
  else if constexpr( OC::is_complete )
  {
    for_each_until_m(m, copy_by_one_checking_each_lambda_unsafe {f, o});
  }
  else
  {
    o += settings.c_out.offset(eve::as(m));
    O limit = o + settings.c_out.count(eve::as(m));

    for_each_until_m(m, copy_by_one_checking_each_lambda_checked {f, o, limit});
  }

  return o;
}

template<typename I, typename L, typename O>
EVE_FORCEINLINE auto
copy_by_countr_zeroes_no_limits(I f, top_bits<L> m, O o) -> O
{
  if constexpr( top_bits<L>::is_aggregated )
  {
    auto [lo, hi] = m.slice();
    o             = copy_by_countr_zeroes_no_limits(f, lo, o);
    return copy_by_countr_zeroes_no_limits(f + (L::size() / 2), hi, o);
  }
  else
  {
    auto im = m.as_int();

    while( im )
    {
      int last_set = std::countr_zero(im);
      f += last_set / top_bits<L>::bits_per_element;

      // 2 shifts avoid shift by full lengh
      im >>= last_set;
      im >>= top_bits<L>::bits_per_element;
      eve::write(eve::read(f++), o++);
    }

    return o;
  }
}

template<typename I, typename L, typename O>
EVE_FORCEINLINE auto
copy_by_countr_zeroes_limited(I f, top_bits<L> m, O& o, O limit) -> O
{
  if constexpr( top_bits<L>::is_aggregated )
  {
    auto [lo, hi] = m.slice();
    o             = copy_by_countr_zeroes_limited(f, lo, o, limit);
    return copy_by_countr_zeroes_limited(f + (L::size() / 2), hi, o, limit);
  }
  else
  {
    auto im = m.as_int();

    while( im )
    {
      if( o == limit ) return o;

      int last_set = std::countr_zero(im);
      f += last_set / top_bits<L>::bits_per_element;
      im >>= last_set;
      im >>= top_bits<L>::bits_per_element;
      eve::write(eve::read(f++), o++);
    }

    return o;
  }
}

template<typename Settings, typename I, typename L, typename O>
EVE_FORCEINLINE auto
copy_by_countr_zeroes(Settings settings, I f, top_bits<L> m, O o) -> O
{
  static_assert(std::same_as<typename Settings::cond_in_t, ignore_none_>);
  using OC = typename Settings::cond_out_t;

  if constexpr( OC::is_complete ) { return copy_by_countr_zeroes_no_limits(f, m, o); }
  else
  {
    o += settings.c_out.offset(eve::as(m));
    O limit = o + settings.c_out.count(eve::as(m));
    return copy_by_countr_zeroes_limited(f, m, o, limit);
  }
}

template<typename Settings, typename I, typename L, typename O>
EVE_FORCEINLINE auto
compress_copy_scalar_impl_(EVE_SUPPORTS(cpu_), Settings settings, I f, L m, O o) -> O
{
  using IC = typename Settings::cond_in_t;

  if constexpr( Settings::is_sparse && L::size() <= 4 )
  {
    return compress_copy_scalar_impl(
        compress_callable_settings(settings.safety, dense, settings.c_in, settings.c_out), f, m, o);
  }
  else if constexpr( !IC::is_complete )
  {
    return compress_copy_scalar_impl(
        compress_callable_settings(settings.safety, settings.density, ignore_none, settings.c_out),
        f,
        top_bits {m, settings.c_in},
        o);
  }
  // on x86 or for sparse, we should just go top_bits.
  else if constexpr( logical_simd_value<L>
                     && (Settings::is_sparse || current_api >= sse2 || L::size() > 4) )
  {
    // Some experiments show that doing "none" here is not beneficial even for expensive ~ish
    // top bits.
    return compress_copy_scalar_impl(settings, f, top_bits {m}, o);
  }
  else if constexpr( Settings::is_sparse ) return copy_by_countr_zeroes(settings, f, m, o);
  else return copy_by_one_checking_each(settings, f, m, o);
}

}

namespace eve
{

struct compress_copy_scalar_core
{
  template<typename Settings, typename I, logical_simd_value L, typename O>
  EVE_FORCEINLINE auto operator()(Settings settings, I f_, L m, O o_) const -> unaligned_t<O>
  {
    using CIn  = typename Settings::cond_in_t;
    using COut = typename Settings::cond_out_t;

    auto f = eve::unalign(f_);
    auto o = eve::unalign(o_);

    if constexpr( CIn::is_complete && !CIn::is_inverted ) return o;
    else if constexpr( COut::is_complete && !COut::is_inverted ) return o;
    else if constexpr( !Settings::is_safe && !CIn::is_complete && !COut::is_complete )
    {
      auto settings2 = detail::compress_callable_settings {
          safe, settings.density, settings.c_in, settings.c_out};
      return operator()(settings2, f, m, o);
    }
    else return detail::compress_copy_scalar_impl(settings, f, m, o);
  }

  template<typename Settings, typename I, logical_simd_value L, typename O>
  EVE_FORCEINLINE auto operator()(Settings settings,
                                  I        f,
                                  as_wide_t<value_type_t<I>, typename L::cardinal_type>,
                                  L m,
                                  O o) const -> unaligned_t<O>
  {
    return operator()(settings, f, m, eve::unalign(o));
  }
};

inline constexpr auto compress_copy_scalar =
    detail::compress_callable<compress_copy_scalar_core> {};

}
