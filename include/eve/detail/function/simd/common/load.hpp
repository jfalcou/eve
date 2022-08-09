//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/memory.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/memory/soa_ptr.hpp>
#include <eve/module/core/regular/replace.hpp>
#include <eve/module/core/regular/safe.hpp>
#include <eve/module/core/regular/unsafe.hpp>
#include <eve/module/core/regular/unalign.hpp>
#include <eve/traits/wide_value_type.hpp>

#include <iterator>

namespace eve::detail
{
  //================================================================================================
  // SIMD short-cut
  // Those overloads redirect simpler load calls to the actual, fully-fledged load implementation
  // with all missing elements pre-computed
  //================================================================================================
  template<data_source Ptr>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), Ptr ptr) noexcept
                ->  decltype(load(ignore_none, safe, eve::as<wide_value_type_t<Ptr>>{}, ptr))
  {
    return load(ignore_none, safe, eve::as<wide_value_type_t<Ptr>>{}, ptr);
  }

  template<data_source Ptr, std::ptrdiff_t N>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), Ptr ptr, fixed<N> const &) noexcept
                ->  decltype(load(ignore_none, safe, as<as_wide_t<value_type_t<Ptr>,fixed<N>>>{}, ptr))
  {
    return load(ignore_none, safe, as<as_wide_t<value_type_t<Ptr>,fixed<N>>>{}, ptr);
  }

  template<data_source Ptr, simd_value Wide>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), Ptr ptr, as<Wide> const &) noexcept
                ->  decltype(load(ignore_none, safe, eve::as<Wide>{}, ptr))
  {
    return load(ignore_none, safe, eve::as<Wide>{}, ptr);
  }

  template<data_source Ptr, decorator Decorator>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), Decorator const& d, Ptr ptr) noexcept
                ->  decltype(load(ignore_none, d, eve::as<wide_value_type_t<Ptr>>{}, ptr))
  {
    return load(ignore_none, d, eve::as<wide_value_type_t<Ptr>>{}, ptr);
  }

  template<data_source Ptr, decorator Decorator, std::ptrdiff_t N>
  EVE_FORCEINLINE   auto load_( EVE_SUPPORTS(cpu_)
                              , Decorator const& d, Ptr ptr, fixed<N> const&
                              ) noexcept
                ->  decltype( load(ignore_none, d, as<as_wide_t<value_type_t<Ptr>,fixed<N>>>{}, ptr) )
  {
    return load(ignore_none, d, as<as_wide_t<value_type_t<Ptr>,fixed<N>>>{}, ptr);
  }

  template<data_source Ptr, decorator Decorator, simd_value Wide>
  EVE_FORCEINLINE   auto load_( EVE_SUPPORTS(cpu_)
                              , Decorator const& d, Ptr ptr, as<Wide> const&
                              ) noexcept
                ->  decltype( load(ignore_none, d, eve::as<Wide>{}, ptr) )
  {
    return load(ignore_none, d, eve::as<Wide>{}, ptr);
  }

  template<relative_conditional_expr C, data_source Ptr>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr) noexcept
                ->  decltype( load(cond, safe, as<wide_value_type_t<Ptr>>{}, ptr) )
  {
    return load(cond, safe, as<wide_value_type_t<Ptr>>{}, ptr);
  }

  template<relative_conditional_expr C, data_source Ptr, std::ptrdiff_t N>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr, fixed<N> const&) noexcept
                ->  decltype( load( cond, safe, as<as_wide_t<value_type_t<Ptr>,fixed<N>>>{}, ptr ) )
  {
    return load( cond, safe, as<as_wide_t<value_type_t<Ptr>,fixed<N>>>{}, ptr );
  }

  template<relative_conditional_expr C, data_source Ptr, simd_value Wide>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr, as<Wide> const&) noexcept
                ->  decltype( load( cond, safe, as<Wide>{}, ptr ) )
  {
    return load( cond, safe, as<Wide>{}, ptr );
  }

  template<relative_conditional_expr C, decorator Decorator, data_source Ptr>
  EVE_FORCEINLINE   auto load_( EVE_SUPPORTS(cpu_)
                              , C const &cond, Decorator const& d,Ptr ptr
                              ) noexcept
                ->  decltype( load(cond, d, as<wide_value_type_t<Ptr>>{}, ptr) )
  {
    return load(cond, d, as<wide_value_type_t<Ptr>>{}, ptr);
  }

  template<relative_conditional_expr C, decorator Decorator, data_source Ptr, std::ptrdiff_t N>
  EVE_FORCEINLINE   auto load_( EVE_SUPPORTS(cpu_)
                              , C const &cond, Decorator const& d,Ptr ptr, fixed<N> const&
                              ) noexcept
                ->  decltype( load( cond, d, as<as_wide_t<value_type_t<Ptr>,fixed<N>>>{}, ptr ) )
  {
    return load( cond, d, as<as_wide_t<value_type_t<Ptr>,fixed<N>>>{}, ptr );
  }

  template<relative_conditional_expr C, decorator Decorator, data_source Ptr, simd_value Wide>
  EVE_FORCEINLINE   auto load_( EVE_SUPPORTS(cpu_)
                              , C const &cond, Decorator const& d,Ptr ptr, as<Wide> const&
                              ) noexcept
                ->  decltype( load( cond, d, as<Wide>{}, ptr ) )
  {
    return load( cond, d, as<Wide>{}, ptr );
  }

  //================================================================================================
  // Load helper
  //================================================================================================
  template<typename Pack, typename Iterator>
  EVE_FORCEINLINE auto piecewise_load(eve::as<Pack> const &, Iterator ptr) noexcept
  {
    auto impl = [&](auto... I)
    {
      auto deref = [&](auto p, auto const &i) { std::advance(p, i); return *p; };
      return Pack(deref(ptr, static_cast<std::ptrdiff_t>(I))...);
    };

    return apply<Pack::size()>(impl);
  }

  template<typename Wide, typename Pointer>
  EVE_FORCEINLINE auto aggregate_load(eve::as<Wide> const &, Pointer ptr) noexcept
  {
    Wide that;

    auto cast = []<typename Ptr, typename Sub>(Ptr ptr, as<Sub>)
    {
      using type = element_type_t<Wide>;
      using a_p = eve::aligned_ptr<const type, cardinal_t<Sub>>;
      if constexpr (std::is_pointer_v<Ptr>) return ptr;
      else                                  return a_p{ptr.get()};
    };

    that.storage().apply
    (
      [&]<typename... Sub>(Sub&... v)
      {
        int offset = 0;
        (((v = Sub(cast(ptr, as<Sub>{}) + offset), offset += Sub::size()), ...));
      }
    );

    return that;
  }

  //================================================================================================
  // Load from a range [b, e(
  //================================================================================================
  template<std::input_iterator Iterator>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), Iterator b, Iterator e) noexcept
  {
    using base = typename std::iterator_traits<Iterator>::value_type;
    return load(ignore_none, safe, as<as_wide_t<base>>{}, b, e);
  }

  template<std::input_iterator Iterator, typename Wide>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), as<Wide> const&, Iterator b, Iterator e) noexcept
  {
    return load(ignore_none, safe, as<Wide>{}, b, e);
  }

  template<std::input_iterator Iterator, typename Pack>
  EVE_FORCEINLINE Pack
  load_ ( EVE_SUPPORTS(cpu_), ignore_none_ const&, safe_type const&
        , eve::as<Pack> const &tgt, Iterator b, [[maybe_unused]] Iterator e
        ) noexcept
  {
    return piecewise_load(tgt,b);
  }

  //================================================================================================
  // Load from pointer - Emulation
  //================================================================================================
  template<typename T, typename N, data_source Ptr>
  EVE_FORCEINLINE wide<T, N> load_( EVE_SUPPORTS(cpu_), ignore_none_ const&, safe_type const&
                                  , eve::as<wide<T, N>> const &tgt, Ptr ptr
                                  ) noexcept
  requires simd_compatible_ptr<Ptr,wide<T, N>> && std::same_as<abi_t<T, N>, emulated_>
  {
    return piecewise_load(tgt, unalign(ptr));
  }

  //================================================================================================
  // Aggregation
  //================================================================================================
  template<typename T, typename N, data_source Ptr>
  EVE_FORCEINLINE wide<T, N> load_( EVE_SUPPORTS(cpu_), ignore_none_ const&, safe_type const&
                                  , eve::as<wide<T, N>> const &tgt, Ptr ptr
                                  ) noexcept
  requires(simd_compatible_ptr<Ptr,wide<T, N>> && std::same_as<abi_t<T, N>, aggregated_>)
  {
    return aggregate_load(tgt,ptr);
  }

  //================================================================================================
  // Bundle
  //================================================================================================
  template<typename N, relative_conditional_expr C, typename ... Ptrs>
  EVE_FORCEINLINE wide<value_type_t<soa_ptr<Ptrs...>>, N>
  load_( EVE_SUPPORTS(cpu_)
         , C const& c
         , decorator auto const& mode
         , eve::as<wide<value_type_t<soa_ptr<Ptrs...>>, N>> const &
         , soa_ptr<Ptrs...> ptr
        ) noexcept
  {
    wide<value_type_t<soa_ptr<Ptrs...>>, N> that;
    if constexpr ( C::has_alternative )
    {
      kumi::for_each( [=]<typename M>(M& m, auto part_alt, auto p) {
            auto new_c = c.map_alternative([&](auto) { return part_alt; });
            m = load(new_c,mode,as<M>{},p);
          }
          , that.storage(), c.alternative, ptr
          );
    }
    else
    {
      kumi::for_each( [=]<typename M>(M& m, auto p) { m = load(c,mode,as<M>{},p); }
                     , that.storage(), ptr
                     );
    }

    return that;
  }

  //================================================================================================
  // Basic logical support
  //================================================================================================
  template<typename T, typename N, data_source Pointer>
  EVE_FORCEINLINE logical<wide<T, N>>
  load_ ( EVE_SUPPORTS(cpu_), ignore_none_ const&, safe_type const&
        , eve::as<logical<wide<T, N>>> const &tgt, Pointer ptr
        ) noexcept
  requires( dereference_as<logical<T>, Pointer>::value && !x86_abi<abi_t<T, N>> )
  {
    if constexpr ( std::same_as<abi_t<T, N>, aggregated_> ) return aggregate_load(tgt,ptr);
    else return
      bit_cast
            ( [&]() -> wide<T, N>
              {
                using wtg = eve::as<wide<T, N>>;
                return load(ignore_none,safe,wtg{}, ptr_cast<T>(ptr));
              }()
            , tgt
            );
  }
}
