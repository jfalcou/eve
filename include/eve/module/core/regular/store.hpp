//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/concept/memory.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/unalign.hpp>
#include <eve/module/core/regular/store_equivalent.hpp>
#include <eve/memory/pointer.hpp>

namespace eve::_
{
  template<typename T, typename Ptr>
  constexpr bool can_be_stored() noexcept
  {
    if constexpr (scalar_pointer<Ptr>)
    {
      return !std::is_const_v<std::remove_pointer_t<unaligned_t<Ptr>>>;
    }
    else if constexpr (has_store_equivalent<T, Ptr>)
    {
      using eq_t = decltype(store_equivalent(ignore_none, std::declval<T>(), std::declval<Ptr>()));
      return can_be_stored<kumi::element_t<1, eq_t>, kumi::element_t<2, eq_t>>();
    }
    else if constexpr (product_type<T> && kumi::concepts::product_type<Ptr>)
    {
      return []<std::size_t... I>(std::index_sequence<I...>)
      {
        return (can_be_stored<decltype(get<I>(std::declval<T>())), kumi::element_t<I, Ptr>>()
               && ...);
      }(std::make_index_sequence<kumi::size_v<Ptr>>{});
    }
    else
    {
      return requires(Ptr p, T v) { p.store(options<>{}, v); };
    }
  }
}

namespace eve
{
  template<typename T, typename SIMD>
  concept writable_simd_compatible_ptr = simd_compatible_ptr<T, SIMD>
                                      && _::can_be_stored<SIMD, T>();

  template<typename T, typename SIMD>
  concept writable_logical_simd_compatible_ptr = logical_simd_compatible_ptr<T, SIMD>
                                              && !std::is_const_v<std::remove_pointer_t<unaligned_t<T>>>;

  template<typename Options>
  struct store_t : relative_conditional_callable<store_t, Options>
  {
    template<arithmetic_simd_value T, writable_simd_compatible_ptr<T> Ptr>
    EVE_ABI void operator()(T value, Ptr ptr) const noexcept
    {
      return EVE_DISPATCH_CALL(value, ptr);
    }

    template<logical_simd_value T, writable_logical_simd_compatible_ptr<T> Ptr>
    EVE_ABI void operator()(T value, Ptr ptr) const noexcept
    {
      return EVE_DISPATCH_CALL(value, ptr);
    }

    EVE_CALLABLE_OBJECT(store_t, store_);
  };

  //================================================================================================
  //! @addtogroup eve_memory
  //! @{
  //!   @var store
  //!   @brief Store the elements of a [SIMD value](@ref eve::simd_value) into the given memory
  //!          location.
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!     // Regular overload
  //!     template<arithmetic_simd_value T, writable_simd_compatible_ptr<T> Ptr>
  //!     void store(T value, Ptr ptr) noexcept;                                           // 1
  //!
  //!     template<logical_simd_value T, writable_logical_simd_compatible_ptr<T> Ptr>
  //!     void store(T value, Ptr ptr) noexcept;                                           // 1
  //!
  //!     // Lanes masking
  //!     auto store[conditional_expr auto c](/* any of the above overloads */) noexcept;  // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!    * `value` : The [SIMD value](@ref eve::simd_value) to store.
  //!    * `ptr`   : A pointer to the memory location where the elements of `value` will be stored.
  //!    * `c`     : A [relative conditional expression](@ref eve::relative_conditional_expr) masking
  //!                the operation.
  //!
  //!   **Overloads**
  //!
  //!    1. Stores the elements of `value` into the memory location pointed to by `ptr`.
  //!    2. Same as 1. but lanes masked by the condition `c` will not be stored.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/store.cpp}
  //================================================================================================
  inline constexpr auto store = functor<store_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/core/regular/impl/store.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/store.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/store.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/store.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/store.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/module/core/regular/impl/simd/riscv/store.hpp>
#endif
