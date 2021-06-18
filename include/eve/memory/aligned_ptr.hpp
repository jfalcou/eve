//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/memory/align.hpp>
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/is_aligned.hpp>
#include <eve/traits/alignment.hpp>
#include <eve/traits/element_type.hpp>

#include <compare>
#include <concepts>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //================================================================================================
  //! @brief Wrapper for non-owning aligned pointers
  //!
  //! **Required header:** `#include <eve/memory/aligned_ptr.hpp>`
  //!
  //! aligned_ptr is a non-owning pointer that binds a preexisting aligned memory and prevent
  //! any alignment-altering operations to be performed. The bound pointer must be aligned so that
  //! they can be used to load at most `Lanes` element of type `Type` natively.
  //!
  //! Rebinding to another pointer is allowed only if the new pointer's alignment is compatible
  //! with the current aligned_ptr constraints.
  //!
  //! An aligned_ptr may alternatively own no object, in which case it is called  empty.
  //!
  //! @tparam Type  Pointee type
  //! @tparam Lanes Alignment constraint to uphold. Default value is computed to be compatible with
  //!               current SIMD ABI requirements.
  //================================================================================================
  template< typename Type
          , typename Lanes = expected_cardinal_t<Type>
          >
#if !defined(EVE_DOXYGEN_INVOKED)
  requires (!std::same_as<Type, void>)
#endif
  struct aligned_ptr
  {
    //! The value type associated to the held pointer
    using value_type = std::remove_const_t<Type>;

    //! The @nullable type currently held.
    using pointer = std::add_pointer_t<Type>;

    //! Generate an aligned_ptr with a different type but same `Lanes`
    template<typename T> using rebind = aligned_ptr<T,Lanes>;

    //! Return the value of the alignment constraint
    static constexpr auto alignment() noexcept { return Lanes::value * sizeof(Type); }

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================
    //! Default constructor.
    aligned_ptr() noexcept : pointer_(nullptr) {}

    //! Set the held pointer to `nullptr`
    aligned_ptr(std::nullptr_t) noexcept : pointer_(nullptr) {}

    //! Construct an aligned_ptr from a pointer.
    //! Behavior is undefined if `p` is not aligned on `Lanes`.
    aligned_ptr(pointer p) noexcept : pointer_(p)
    {
      EVE_ASSERT( is_aligned<alignment()>(p)
                , (void *)(p) << " is not aligned on " << Lanes::value
                              << " elements (or " << alignment() << " bytes)."
                );
    }

    //! Construct an aligned_ptr from another one with a compatible alignment constraint
    template<typename L>
    aligned_ptr(aligned_ptr<Type, L> p) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( L::value >= Lanes::value)
#endif
              : pointer_(p.get())
    {}

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! Assign from another aligned_ptr with a compatible alignment constraint
    template<typename L>
    aligned_ptr &operator=(aligned_ptr<Type, L> p) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( L::value >= Lanes::value)
#endif
    {
      pointer_ = p.get();
      return *this;
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Pointer arithmetic
    //! @{
    //==============================================================================================
    //! @brief Add an offset to the held pointer.
    //! Behavior is undefined if the offset forces the pointer to become misaligned
    aligned_ptr &operator+=(std::ptrdiff_t o) noexcept
    {
      EVE_ASSERT( is_aligned<alignment()>(pointer_ + o)
                , (void *)(pointer_)  << " + " << o
                                      << " is not aligned on " << Lanes::value << "."
                );

      pointer_ += o;
      return *this;
    }

    //! @brief Substract an offset to the held pointer.
    //! Behavior is undefined if the offset forces the pointer to become misaligned
    aligned_ptr &operator-=(std::ptrdiff_t o) noexcept
    {
      EVE_ASSERT( is_aligned<alignment()>(pointer_ - o)
                , (void *)(pointer_)  << " - " << o
                                      << " is not aligned on " << Lanes::value << "."
                );

      pointer_ -= o;
      return *this;
    }

    //! @brief Pre-increments the held pointer.
    //! Does not participate in overload resolution if `Lanes != 1`
    aligned_ptr &operator++() noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(alignment() == 1)
#endif
    {
      pointer_++;
      return *this;
    }

    //! @brief Post-increments the held pointer.
    //! Does not participate in overload resolution if `Lanes != 1`
    aligned_ptr operator++(int) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(alignment() == 1)
#endif
    {
      aligned_ptr tmp(*this);
      this->      operator++();
      return tmp;
    }

    //! @brief Pre-decrements the held pointer.
    //! Does not participate in overload resolution if `Lanes != 1`
    aligned_ptr &operator--() noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(alignment() == 1)
#endif
    {
      pointer_--;
      return *this;
    }

    //! @brief Post-decrements the held pointer.
    //! Does not participate in overload resolution if `Lanes != 1`
    aligned_ptr operator--(int) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(alignment() == 1)
#endif
    {
      aligned_ptr tmp(*this);
      this->      operator--();
      return tmp;
    }
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Other members
    //! @{
    //==============================================================================================
    //! Exchanges the content of the aligned_ptr with those of `that`.
    void swap(aligned_ptr &that) noexcept { std::swap(pointer_, that.pointer_); }

    //! Compares aligned_ptr lexicographically.
    auto operator<=>(const aligned_ptr<Type, Lanes>&) const = default;
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Observers
    //! @{
    //==============================================================================================
    //! Checks if there is an associated held object
    explicit operator bool() const noexcept { return pointer_ != nullptr; }

    //! Returns the pointer to the held object
    explicit operator pointer() const noexcept { return pointer_; }

    //! Returns the pointer to the held object
    pointer  get() const noexcept { return pointer_; }

    //! Dereferences pointer to the held object
    decltype(auto) operator*() const  noexcept { return *pointer_; }

    //! Dereferences pointer to the held object
    decltype(auto) operator*()        noexcept { return *pointer_; }

    //! Dereferences pointer to the held object
    decltype(auto) operator-> () const  noexcept { return pointer_; }

    //! Dereferences pointer to the held object
    decltype(auto) operator-> ()        noexcept { return pointer_; }

    //! Indexed array to the underlying array
    Type const &operator[](std::size_t i) const noexcept { return pointer_[ i ]; }

    //! Indexed array to the underlying array
    Type &      operator[](std::size_t i)       noexcept { return pointer_[ i ]; }
    //==============================================================================================
    //! @}
    //==============================================================================================

    private:
    pointer pointer_;
  };

  //================================================================================================
  //! @brief Checks if an aligned_ptr is aligned on a given alignment.
  //! @param  ptr aligned_ptr to checks
  //! @tparam A   Alignment constraint to verify
  //! @return A boolean indicating if `ptr` is compatible with the `Other` alignment.
  //================================================================================================
  template<std::size_t A, typename T, typename Other>
  constexpr bool is_aligned(aligned_ptr<T, Other> const &ptr) noexcept
  {
    return is_aligned<A>(ptr.get());
  }

  //================================================================================================
  //! @}
  //================================================================================================

  template<typename T, typename A>  struct element_type<aligned_ptr<T,A>> { using type = T; };
  template<typename T>              struct element_type<aligned_ptr<T>>   { using type = T; };

  template<typename T1, typename A1, typename T2, typename A2>
  bool operator==(aligned_ptr<T1, A1> lhs, aligned_ptr<T2, A2> rhs) noexcept
  {
    return lhs.get() == rhs.get();
  }

  template<typename T, typename A>
  bool operator==(aligned_ptr<T, A> lhs, T* rhs) noexcept
  {
    return lhs.get() == rhs;
  }

  template<typename T, typename A>
  bool operator==(T* lhs, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() == lhs;
  }

  template<typename T, typename A>
  bool operator==(aligned_ptr<T, A> lhs, std::nullptr_t) noexcept
  {
    return lhs.get() == nullptr;
  }

  template<typename T, typename A>
  bool operator==(std::nullptr_t, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() == nullptr;
  }

  template<typename T1, typename A1, typename T2, typename A2>
  bool operator!=(aligned_ptr<T1, A1> lhs, aligned_ptr<T2, A2> rhs) noexcept
  {
    return lhs.get() != rhs.get();
  }

  template<typename T, typename A>
  bool operator!=(aligned_ptr<T, A> lhs, T* rhs) noexcept
  {
    return lhs.get() != rhs;
  }

  template<typename T, typename A>
  bool operator!=(T* lhs, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() != lhs;
  }

  template<typename T, typename A>
  bool operator!=(aligned_ptr<T, A> lhs, std::nullptr_t) noexcept
  {
    return lhs.get() !=nullptr;
  }

  template<typename T, typename A>
  bool operator!=(std::nullptr_t, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get()!= nullptr;
  }

  template<typename Type, typename Lanes>
  void swap(aligned_ptr<Type, Lanes> &lhs, aligned_ptr<Type, Lanes> &rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template<typename Type, typename Lanes>
  aligned_ptr<Type, Lanes> operator-(aligned_ptr<Type, Lanes> const &p,std::ptrdiff_t o) noexcept
  {
    auto that = p;
    return that -= o;
  }

  template <typename Type, typename Lanes>
  std::ptrdiff_t operator-(aligned_ptr<Type, Lanes> const& lhs, aligned_ptr<Type, Lanes> const& rhs) noexcept
  {
    return lhs.get() - rhs.get();
  }

  template <typename Type, typename Lanes>
  std::ptrdiff_t operator-(aligned_ptr<Type, Lanes> const& lhs, Type* rhs) noexcept
  {
    return lhs.get() - rhs;
  }

  template <typename Type, typename Lanes>
  std::ptrdiff_t operator-(Type* lhs, aligned_ptr<Type, Lanes> const& rhs) noexcept
  {
    return lhs - rhs.get();
  }

  template<typename Type, typename Lanes>
  aligned_ptr<Type, Lanes> operator+(aligned_ptr<Type, Lanes> const &p, std::ptrdiff_t o) noexcept
  {
    auto that = p;
    return that += o;
  }

  template<typename Type, typename Lanes>
  aligned_ptr<Type, Lanes> operator+(std::ptrdiff_t                      o,
                                         aligned_ptr<Type, Lanes> const &p) noexcept
  {
    auto that = p;
    return that += o;
  }

  //================================================================================================
  //! @relates eve::aligned_ptr
  //!
  //! @brief Constructs an aligned_ptr from a pointer `ptr`.
  //! Behavior is undefined if `ptr` does not satisfy alignment constraint `Lanes`.
  //!
  //! @param ptr    Pointer to wrap
  //! @param lanes  Lanes count to satisfy
  //! @return An aligned_ptr holding`ptr` with the proper alignment constraint.
  //================================================================================================
  template<typename Lanes, typename Type>
#if !defined(EVE_DOXYGEN_INVOKED)
  aligned_ptr<Type, Lanes> as_aligned(Type* ptr, Lanes ) noexcept
#else
  aligned_ptr<Type, Lanes> as_aligned(Type* ptr, Lanes lanes) noexcept
#endif
  {
    return {ptr};
  }

  //================================================================================================
  //! @relates eve::aligned_ptr
  //!
  //! @brief Constructs an aligned_ptr from a pointer `ptr`.
  //! Behavior is undefined if `ptr` does not satisfy the default alignment constraint.
  //!
  //! @param  ptr       Pointer to wrap
  //! @return An aligned_ptr holding`ptr` with the proper alignment constraint.
  //================================================================================================
  template<typename Type>
  aligned_ptr<Type> as_aligned(Type* ptr) noexcept
  {
    return {ptr};
  }

  //! @overload
  template<typename Lanes, typename Type>
  aligned_ptr<Type const, Lanes> as_aligned(Type const *ptr, Lanes) noexcept
  {
    return {ptr};
  }

  //! @overload
  template<typename Type>
  aligned_ptr<Type const> as_aligned(Type const *ptr) noexcept
  {
    return {ptr};
  }

  //================================================================================================
  //! @relates eve::aligned_ptr
  //!
  //! @brief Computes an address lesser or equal to `p` which is satisfy the alignment constraint of
  //! SIMD registers of size `Lanes`.
  //!
  //! @param p      Pointer to realign
  //! @param width  SIMD cardinal to use as alignment constraint
  //! @return An aligned_ptr holding the realigned pointer with the proper alignment constraint.
  //! @see previous_aligned_address(T*)
  //================================================================================================
  template <typename T, typename Lanes>
  #if !defined(EVE_DOXYGEN_INVOKED)
  EVE_FORCEINLINE auto previous_aligned_address(T* p, Lanes) noexcept
  #else
  EVE_FORCEINLINE auto previous_aligned_address(T* p, Lanes width) noexcept
  #endif
  {
    return eve::aligned_ptr<T, Lanes>{ eve::align(p, eve::under{Lanes::value*sizeof(T)}) };
  }

  //================================================================================================
  //! @relates eve::aligned_ptr
  //!
  //! @brief Computes an address lesser or equal to `p` which is satisfy the alignment constraint of
  //! current architecture's SIMD register.
  //!
  //! @param p      Pointer to realign
  //! @return An aligned_ptr holding the realigned pointer with the proper alignment constraint.
  //! @see previous_aligned_address(T*, Cardinal)
  //================================================================================================
  template <typename T>
  EVE_FORCEINLINE auto previous_aligned_address(T* p) noexcept
  {
    return previous_aligned_address(p, eve::expected_cardinal<std::remove_cvref_t<T>>{});
  }

  //================================================================================================
  //  Specialisation for pointer_alignment
  //================================================================================================
  template<typename Type, typename Lanes>
  struct  pointer_alignment<aligned_ptr<Type, Lanes>>
        : std::integral_constant<std::size_t,aligned_ptr<Type, Lanes>::alignment()>
  {};
}
