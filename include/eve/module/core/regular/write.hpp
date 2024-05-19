//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/overload.hpp>
#include <eve/memory/soa_ptr.hpp>

namespace eve
{
  template<typename Options>
  struct write_t : callable<write_t, Options>
  {
    template<typename Ptr, scalar_value V>
    requires requires(Ptr p, V v) { *p = v; }
    EVE_FORCEINLINE void operator()(V v, Ptr ptr) const noexcept{ return EVE_DISPATCH_CALL(v,ptr); }

    template<typename Writeable, scalar_value V>
    requires requires(Writeable p, V v) { p.write(v); }
    EVE_FORCEINLINE void operator()(V v, Writeable p) const noexcept{ return EVE_DISPATCH_CALL(v,p); }

    template<typename... Ptrs, scalar_value V>
    EVE_FORCEINLINE void operator()(V v, soa_ptr<Ptrs...> ptr) const noexcept{ return EVE_DISPATCH_CALL(v,ptr); }

    EVE_CALLABLE_OBJECT(write_t, write_);
  };

  //================================================================================================
  //! @addtogroup memory
  //! @{
  //!   @var write
  //!   @brief Callable object writing a scalar value to memory
  //!
  //!   `operator*` based interface used in the standard has notorious issues with proxy references.
  //!   To prevent those issues when dealing with complex, potentially SIMD-aware iterators, `eve::write` is to be used.
  //!
  //!   **Defined in Header**
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
  //!     template<typename Ptr, scalar_value V>
  //!     requires requires(Ptr p, V v) { *p = v; }
  //!     EVE_FORCEINLINE void operator()(V v, Ptr p) const noexcept;               // 1
  //!
  //!     template<typename Writeable, scalar_value V>
  //!     requires requires(Writeable p, V v) { p.write(v); }
  //!     EVE_FORCEINLINE void operator()(V v, Writeable p) const noexcept;         // 2
  //!
  //!     template<typename... Ptrs, scalar_value V>
  //!     EVE_FORCEINLINE void operator()(V v, soa_ptr<Ptrs...> p) const noexcept;  // 3
  //!   }
  //!   @endcode
  //!
  //!   1. Write the [scalar](@ref eve::scalar_value) `v` into the memory pointed by `p`;
  //!   2. Write the [scalar](@ref eve::scalar_value) `v` into the memory managed by the object `p`;
  //!   3. Write the [scalar](@ref eve::scalar_value) `v` into the memory pointed by SoA pointer `p`;
  //!
  //!   **Parameters**
  //!
  //!   * `v`: [scalar](@ref eve::scalar_value) to write to memory.
  //!   * `p`: A pointer or rich iterator to write to.
  //!
  //! @}
  //================================================================================================
  inline constexpr auto write = functor<write_t>;
}

namespace eve::detail
{
  template<callable_options O, typename Ptr, typename V>
  EVE_FORCEINLINE void write_(EVE_REQUIRES(cpu_), O const&, V v, Ptr p) noexcept
  {
    if constexpr(requires { p.write(v); })   p.write(v);
    else                                    *p = v;
  }

  template<callable_options O,  typename... Ptrs, typename V>
  EVE_FORCEINLINE void write_(EVE_REQUIRES(cpu_), O const&, V v, soa_ptr<Ptrs...> ptr) noexcept
  {
    kumi::for_each(write, v, ptr);
  }
}
