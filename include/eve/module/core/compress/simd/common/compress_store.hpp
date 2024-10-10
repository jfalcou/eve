//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/memory/stack_buffer.hpp>
#include <eve/module/core/regular/safe.hpp>
#include <eve/module/core/regular/store.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve
{

struct compress_store_core
{
  template<typename Settings, simd_value T, logical_simd_value U, typename O>
  EVE_FORCEINLINE auto operator()(Settings settings, T x, U m, O o) const -> unaligned_t<O>
  {
    using CIn  = typename Settings::cond_in_t;
    using COut = typename Settings::cond_out_t;

    if constexpr( CIn::is_complete && !CIn::is_inverted ) return o;
    else if constexpr( COut::is_complete && !COut::is_inverted ) return o;
    else if constexpr( has_store_equivalent<T, O> )
    {
      auto [c_out1, x1, o1] = store_equivalent(settings.c_out, x, o);
      auto res1             = operator()(
          detail::compress_callable_settings(settings.safety, dense, settings.c_in, c_out1),
          x1,
          m,
          o1);
      return unalign(o) + (res1 - o1);
    }
    else if constexpr( !COut::is_complete && !std::same_as<COut, keep_first> )
    {
      auto   offset = settings.c_out.offset(as{x});
      auto   count  = settings.c_out.count(as{x});
      return operator()(detail::compress_callable_settings(
                            settings.safety, dense, settings.c_in, keep_first(count)),
                        x,
                        m,
                        unalign(o) + offset);
    }
    else if constexpr( Settings::is_safe )
    {
      stack_buffer<T> buf;

      auto unsafe_settings =
          detail::compress_callable_settings(unsafe, dense, settings.c_in, ignore_none);

      auto up_to       =   operator()(unsafe_settings, x, m, buf.ptr());
      std::ptrdiff_t n = up_to - buf.ptr();
      if constexpr( !COut::is_complete ) { n = std::min(n, settings.c_out.count(as{x})); }
      store[keep_first(n)](T(buf.ptr()), o);
      return unalign(o) + n;
    }
    else if constexpr( has_emulated_abi_v<T> )
    {
      auto offset = settings.c_in.offset(as{x});
      auto count  = settings.c_in.count(as{x});
      auto o_     = unalign(o);
      auto limit  = o_ + settings.c_out.count(as{x});

      for( int idx = offset; idx != (int)(offset + count); ++idx )
      {
        if( m.get(idx) )
        {
          if( o_ == limit ) return o_;
          *o_++ = x.get(idx);
        }
      }

      return o_;
    }
    else if constexpr( !COut::is_complete
                       && std::tuple_size_v<decltype(compress[settings.c_in](x, m))> == 1 )
    {
      auto [part, count_] = get<0>(compress[settings.c_in](x, m));
      eve::store[settings.c_out](part, o);
      std::ptrdiff_t count = count_;

      if( !COut::is_complete ) count = std::min(count, settings.c_out.count(as{x}));

      return unalign(o) + count;
    }
    else if( !COut::is_complete )
    {
      auto safe_settings =
          detail::compress_callable_settings(safe, dense, settings.c_in, settings.c_out);
      return operator()(safe_settings, x, m, o);
    }
    else
    {
      auto parts = compress[settings.c_in](x, m);
      auto o_    = unalign(o);

      kumi::for_each(
          [&](auto part_count) mutable
          {
            auto [part, count] = part_count;
            eve::store(part, o_);
            o_ += count;
          },
          parts);

      return o_;
    }
  }
};

inline constexpr auto compress_store = detail::compress_callable_no_density<compress_store_core> {};

}
