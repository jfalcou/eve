//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/module/core/regular/none.hpp>
#include <eve/module/core/regular/read.hpp>
#include <eve/module/core/regular/write.hpp>

namespace eve::detail
{

template<typename I, typename M, typename O> struct copy_by_one_checking_each_lambda_unsafe
{
  I      & f;
  const M& m;
  O      & o;

  void operator()(auto idx)
  {
    eve::write(eve::read(f++), o);
    o += (bool)m.get(idx);
  }
};

template <typename ...Args>
copy_by_one_checking_each_lambda_unsafe(Args...) -> copy_by_one_checking_each_lambda_unsafe<Args...>;

template<typename I, typename M, typename O> struct copy_by_one_checking_each_lambda_checked
{
  I      & f;
  const M& m;
  O      & o;
  O        limit;

  bool operator()(auto idx)
  {
    I cur = f++;
    if( m.get(idx()) )
    {
      if (o == limit) return true;
      eve::write(eve::read(cur), o++);
    }
    return false;
  }
};

template <typename I, typename M, typename O>
copy_by_one_checking_each_lambda_checked(I, M, O, O) -> copy_by_one_checking_each_lambda_checked<I, M, O>;

template<typename Settings, typename I, typename M, typename O>
EVE_FORCEINLINE auto
copy_by_one_checking_each(Settings settings, I f, M m, O o) -> O
{
  static_assert(std::same_as<typename Settings::cond_in_t, ignore_none_>);
  using OC = typename Settings::cond_out_t;

  if constexpr( Settings::is_safe )
  {
    if( eve::none(m) ) return o;
  }
  if constexpr( OC::is_complete )
  {
    detail::for_<0, 1, M::size()>(copy_by_one_checking_each_lambda_unsafe {f, m, o});
  }
  else
  {
    o += settings.c_out.offset(eve::as(m));
    O limit = o + settings.c_out.count(eve::as(m));

    detail::for_until_<0, 1, M::size()>(copy_by_one_checking_each_lambda_checked {f, m, o, limit});
  }

  return o;
}

template<typename Settings, typename I, typename L, typename O>
EVE_FORCEINLINE auto
compress_copy_scalar_(EVE_SUPPORTS(cpu_), Settings settings, I f_, L m, O o) -> O
{
  auto f = unalign(f_);

  using IC = typename Settings::cond_in_t;

  if constexpr( Settings::is_sparse && L::size() <= 4 )
  {
    return compress_copy_scalar(
        compress_callable_settings(settings.safety, dense, settings.c_in, settings.c_out), f, m, o);
  }
  else if constexpr( !IC::is_complete )
  {
    return compress_copy_scalar(
        compress_callable_settings(settings.safety, settings.density, ignore_none, settings.c_out),
        f,
        top_bits {m, settings.c_in},
        o);
  }
  // on x86 or for sparse, we should just go top_bits.
  else if constexpr( logical_simd_value<L> && (Settings::is_sparse || current_api >= sse2) )
  {
    return compress_copy_scalar(settings, f, top_bits {m}, o);
  }
  else return copy_by_one_checking_each(settings, f, m, o);
}

}
