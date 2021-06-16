//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/function/replace.hpp>
#include <eve/function/safe.hpp>
#include <eve/function/unsafe.hpp>

#include <iterator>

namespace eve::detail
{
  //================================================================================================
  // Take a data_source and a Cardinal to determine which wide to build
  //================================================================================================
  template<data_source Ptr, typename Cardinal = void>
  struct loaded_wide : as_wide<typename pointer_traits<Ptr>::value_type, Cardinal>
  {};

  template<data_source Ptr>
  struct loaded_wide<Ptr> : as_wide<typename pointer_traits<Ptr>::value_type>
  {};

  template<data_source Ptr, typename Cardinal = void>
  using loaded_wide_t = typename loaded_wide<Ptr,Cardinal>::type;

  //================================================================================================
  // SIMD short-cut
  // Those overloads redirect simpler load calls to the actual, fully-fledged load implementation
  // with all missing elements pre-computed
  //================================================================================================
  template<data_source Ptr>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), Ptr ptr) noexcept
                ->  decltype(load(ignore_none, safe, eve::as_<loaded_wide_t<Ptr>>{}, ptr))
  {
    return load(ignore_none, safe, eve::as_<loaded_wide_t<Ptr>>{}, ptr);
  }

  template<data_source Ptr, std::ptrdiff_t N>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), Ptr ptr, fixed<N> const &) noexcept
                ->  decltype(load(ignore_none, safe, eve::as_<loaded_wide_t<Ptr,fixed<N>>>{}, ptr))
  {
    return load(ignore_none, safe, eve::as_<loaded_wide_t<Ptr,fixed<N>>>{}, ptr);
  }

  template<data_source Ptr, decorator Decorator>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), Decorator const& d, Ptr ptr) noexcept
                ->  decltype(load(ignore_none, d, eve::as_<loaded_wide_t<Ptr>>{}, ptr))
  {
    return load(ignore_none, d, eve::as_<loaded_wide_t<Ptr>>{}, ptr);
  }

  template<data_source Ptr, decorator Decorator, std::ptrdiff_t N>
  EVE_FORCEINLINE   auto load_( EVE_SUPPORTS(cpu_)
                              , Decorator const& d, Ptr ptr, fixed<N> const&
                              ) noexcept
                ->  decltype( load(ignore_none, d, eve::as_<loaded_wide_t<Ptr,fixed<N>>>{}, ptr) )
  {
    return load(ignore_none, d, eve::as_<loaded_wide_t<Ptr,fixed<N>>>{}, ptr);
  }

  template<relative_conditional_expr C, data_source Ptr>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr) noexcept
                ->  decltype( load(cond, safe, as_<loaded_wide_t<Ptr>>{}, ptr) )
  {
    return load(cond, safe, as_<loaded_wide_t<Ptr>>{}, ptr);
  }

  template<relative_conditional_expr C, data_source Ptr, std::ptrdiff_t N>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), C const &cond, Ptr ptr, fixed<N> const&) noexcept
                ->  decltype( load( cond, safe, as_<loaded_wide_t<Ptr, fixed<N>>>{}, ptr ) )
  {
    return load( cond, safe, as_<loaded_wide_t<Ptr, fixed<N>>>{}, ptr );
  }

  template<relative_conditional_expr C, decorator Decorator, data_source Ptr, std::ptrdiff_t N>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), C const &cond, Decorator const& d,Ptr ptr, fixed<N> const&) noexcept
                ->  decltype( load( cond, d, as_<loaded_wide_t<Ptr, fixed<N>>>{}, ptr ) )
  {
    return load( cond, d, as_<loaded_wide_t<Ptr, fixed<N>>>{}, ptr );
  }

  template<relative_conditional_expr C, decorator Decorator, data_source Ptr>
  EVE_FORCEINLINE   auto load_(EVE_SUPPORTS(cpu_), C const &cond, Decorator const& d,Ptr ptr) noexcept
                ->  decltype( load(cond, safe, as_<loaded_wide_t<Ptr>>{}, ptr) )
  {
    return load(cond, d, as_<loaded_wide_t<Ptr>>{}, ptr);
  }

  //================================================================================================
  // Load helper
  //================================================================================================
  template<typename Pack, typename Iterator>
  EVE_FORCEINLINE auto piecewise_load(eve::as_<Pack> const &, Iterator ptr) noexcept
  {
    auto impl = [&](auto... I)
    {
      auto deref = [&](auto p, auto const &i) { std::advance(p, i); return *p; };
      return Pack(deref(ptr, static_cast<std::ptrdiff_t>(I))...);
    };

    return apply<Pack::size()>(impl);
  }

  template<typename Wide, typename Pointer>
  EVE_FORCEINLINE auto aggregate_load(eve::as_<Wide> const &, Pointer ptr) noexcept
  {
    Wide that;

    auto cast = []<typename Ptr, typename Sub>(Ptr ptr, as_<Sub>)
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
        (((v = Sub(cast(ptr, as_<Sub>{}) + offset), offset += Sub::size()), ...));
      }
    );

    return that;
  }

  //================================================================================================
  // Load from a range [b, e[
  //================================================================================================
  template<std::input_iterator Iterator, typename Pack>
  EVE_FORCEINLINE Pack
  load_ ( EVE_SUPPORTS(cpu_), ignore_none_ const&, safe_type const&
        , eve::as_<Pack> const &tgt, Iterator b, [[maybe_unused]] Iterator e
        ) noexcept
  {
    return piecewise_load(tgt,b);
  }

  //================================================================================================
  // Load from pointer - Emulation
  //================================================================================================
  template<typename T, typename N, data_source Ptr>
  EVE_FORCEINLINE wide<T, N> load_( EVE_SUPPORTS(cpu_), ignore_none_ const&, safe_type const&
                                  , eve::as_<wide<T, N>> const &tgt, Ptr ptr
                                  ) noexcept
  requires simd_compatible_ptr<Ptr,wide<T, N>> && std::same_as<abi_t<T, N>, emulated_>
  {
    return piecewise_load(tgt, as_raw_pointer(ptr));
  }

  //================================================================================================
  // Aggregation
  //================================================================================================
  template<typename T, typename N, data_source Ptr>
  EVE_FORCEINLINE wide<T, N> load_( EVE_SUPPORTS(cpu_), ignore_none_ const&, safe_type const&
                                  , eve::as_<wide<T, N>> const &tgt, Ptr ptr
                                  ) noexcept
  requires(simd_compatible_ptr<Ptr,wide<T, N>> && std::same_as<abi_t<T, N>, aggregated_>)
  {
    return aggregate_load(tgt,ptr);
  }

  //================================================================================================
  // Bundle
  //================================================================================================
  template<typename T, typename N, relative_conditional_expr C, data_source Ptr>
  EVE_FORCEINLINE wide<T, N> load_( EVE_SUPPORTS(cpu_), C const& c, safe_type const&
                                  , eve::as_<wide<T, N>> const &, Ptr ptr
                                  ) noexcept
  requires(std::same_as<abi_t<T, N>, bundle_>)
  {
    wide<T, N> that;
    kumi::for_each( [=]<typename M>(M& m, auto p) { m = load(c,safe,as_<M>{},p); }
                  , that.storage(), ptr
                  );
    return that;
  }

  //================================================================================================
  // Basic logical support
  //================================================================================================
  template<typename T, typename N, data_source Pointer>
  EVE_FORCEINLINE logical<wide<T, N>>
  load_ ( EVE_SUPPORTS(cpu_), ignore_none_ const&, safe_type const&
        , eve::as_<logical<wide<T, N>>> const &tgt, Pointer ptr
        ) noexcept
  requires( dereference_as<logical<T>, Pointer>::value && !x86_abi<abi_t<T, N>> )
  {
    if constexpr ( std::same_as<abi_t<T, N>, aggregated_> ) return aggregate_load(tgt,ptr);
    else return
      bit_cast
            ( [&]() -> wide<T, N>
              {
                using wtg = eve::as_<wide<T, N>>;
                return load(ignore_none,safe,wtg{}, ptr_cast<T>(ptr));
              }()
            , tgt
            );
  }
}
