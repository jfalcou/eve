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
  // Iterator with a member store: checked by the constraint of that member
  template<typename T, typename Ptr>
  inline constexpr bool can_be_stored_v = requires(Ptr p, T v) { p.store(options<>{}, v); };

  // Raw pointer or aligned_ptr: checked for a pointer to const
  template<typename T, scalar_pointer Ptr>
  inline constexpr bool can_be_stored_v<T,Ptr> = !std::is_const_v<std::remove_pointer_t<unaligned_t<Ptr>>>;

  // store_equivalent returns (condition, value, pointer), so elements 1 and 2 of the tuple are the
  // value and the pointer the store goes to
  template<typename T, typename Ptr>
  using store_eq_t = decltype(store_equivalent(ignore_none, std::declval<T>(), std::declval<Ptr>()));

  template<typename T, typename Ptr>
  requires( !scalar_pointer<Ptr> && has_store_equivalent<T,Ptr> )
  inline constexpr bool can_be_stored_v<T,Ptr> = can_be_stored_v<kumi::element_t<1, store_eq_t<T,Ptr>>,
                                                                  kumi::element_t<2, store_eq_t<T,Ptr>>>;

  // Matches the zipped (value, pointer) pairs against kumi::tuple<Ts...> to give the fold its pack
  template<typename Zipped>
  inline constexpr bool all_stored_v = false;

  template<typename... Ts>
  inline constexpr bool all_stored_v<kumi::tuple<Ts...>> = (can_be_stored_v<kumi::element_t<0,Ts>, kumi::element_t<1,Ts>> && ...);

  template<eve::product_type T, kumi::concepts::sized_product_type<kumi::size_v<T>> Ptr>
  requires( !has_store_equivalent<T,Ptr> )
  inline constexpr bool can_be_stored_v<T,Ptr> = all_stored_v<kumi::result::zip_t<T,Ptr>>;
}

namespace eve
{
  template<typename T, typename SIMD>
  concept writable_simd_compatible_ptr = simd_compatible_ptr<T, SIMD>
                                      && _::can_be_stored_v<SIMD, T>;

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
