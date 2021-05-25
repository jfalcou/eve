//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/memory/align.hpp>
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/is_aligned.hpp>
#include <eve/traits/alignment.hpp>
#include <eve/traits/element_type.hpp>
#include <compare>

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
  //! aligned_ptr is a non-owning pointer that binds a preexisting, properly aligned memory and
  //! prevent any alignment-altering operations to be performed. Rebinding to another pointer is
  //! allowed only if the new pointer's alignment is compatible with the current aligned_ptr
  //! constraints.
  //!
  //! An aligned_ptr may alternatively own no object, in which case it is called empty.
  //!
  //! @tparam Type      Pointee type
  //! @tparam Alignment Alignment constraint to uphold. Code is ill-formed if it isn't a power of 2.
  //!         Default value is computed to be compatible with current SIMD ABI requirements.
  //================================================================================================
  template< typename Type
          , std::size_t Alignment = sizeof(Type) * expected_cardinal_v<Type>
          >
#if !defined(EVE_DOXYGEN_INVOKED)
  requires(is_power_of_2(Alignment))
#endif
  struct aligned_ptr
  {
    //! The @nullable type currently held.
    using pointer = std::add_pointer_t<Type>;

    //! The type of the object managed by this aligned_ptr
    using element_type = Type ;

    //! Generate an aligned_ptr with a different type but same `Alignment`
    template<typename T> using rebind = aligned_ptr<T,Alignment>;

    //! Return the value of the alignment constraint
    static constexpr std::size_t alignment() { return Alignment; }

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================
    //! Default constructor.
    aligned_ptr() noexcept : pointer_(nullptr) {}

    //! Set the held pointer to `nullptr`
    aligned_ptr(std::nullptr_t) noexcept : pointer_(nullptr) {}

    //! Construct an aligned_ptr from a pointer.
    //! Behavior is undefined if `p` is not aligned on `Alignment`.
    aligned_ptr(pointer p) noexcept : pointer_(p)
    {
      EVE_ASSERT(is_aligned<Alignment>(p),(void *)(p) << " is not aligned on " << Alignment << ".");
    }

    //! Construct an aligned_ptr from another one with a compatible alignment constraint
    template<typename U, std::size_t A>
    aligned_ptr(aligned_ptr<U, A> p) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(A >= Alignment)
#endif
              : pointer_(static_cast<pointer>(p.get()))
    {}

    //! Construct an aligned_ptr from a aligned_ptr<void> with a compatible alignment constraint
    template<std::size_t A>
    aligned_ptr(aligned_ptr<void, A> p) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(A >= Alignment)
#endif
              : pointer_(static_cast<pointer>(p.get()))
    {}
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! Assign from another aligned_ptr with a compatible alignment constraint
    template<typename U, std::size_t A>
    aligned_ptr &operator=(aligned_ptr<U, A> p) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( (A >= Alignment) && std::convertible_to<U*, pointer> )
#endif
    {
      pointer_ = static_cast<pointer>(p.get());
      return *this;
    }

    //! Assign from an aligned_ptr<void> with a compatible alignment constraint
    template<std::size_t A>
    aligned_ptr &operator=(aligned_ptr<void, A> p) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(A >= Alignment)
#endif
    {
      pointer_ = static_cast<pointer>(p.get());
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
      EVE_ASSERT(is_aligned<Alignment>(pointer_ + o),
                 (void *)(pointer_) << " + " << o << " is not aligned on " << Alignment << ".");

      pointer_ += o;
      return *this;
    }

    //! @brief Substract an offset to the held pointer.
    //! Behavior is undefined if the offset forces the pointer to become misaligned
    aligned_ptr &operator-=(std::ptrdiff_t o) noexcept
    {
      EVE_ASSERT( is_aligned<Alignment>(pointer_ - o)
                , (void *)(pointer_) << " - " << o << " is not aligned on " << Alignment << "."
                );

      pointer_ -= o;
      return *this;
    }

    //! @brief Pre-increments the held pointer.
    //! Does not participate in overload resolution if `Alignment != 1`
    aligned_ptr &operator++() noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(Alignment == 1)
#endif
    {
      pointer_++;
      return *this;
    }

    //! @brief Post-increments the held pointer.
    //! Does not participate in overload resolution if `Alignment != 1`
    aligned_ptr operator++(int) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(Alignment == 1)
#endif
    {
      aligned_ptr tmp(*this);
      this->      operator++();
      return tmp;
    }

    //! @brief Pre-decrements the held pointer.
    //! Does not participate in overload resolution if `Alignment != 1`
    aligned_ptr &operator--() noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(Alignment == 1)
#endif
    {
      pointer_--;
      return *this;
    }

    //! @brief Post-decrements the held pointer.
    //! Does not participate in overload resolution if `Alignment != 1`
    aligned_ptr operator--(int) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(Alignment == 1)
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
    auto operator<=>(const aligned_ptr<Type, Alignment>&) const = default;
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

  #if !defined(EVE_DOXYGEN_INVOKED)
  template<std::size_t Alignment>  requires(is_power_of_2(Alignment))
  struct aligned_ptr<void, Alignment>
  {
    using pointer = void *;

    template<typename T> using rebind = aligned_ptr<T,Alignment>;

    static constexpr std::size_t alignment() { return Alignment; }

    aligned_ptr() noexcept {}
    aligned_ptr(std::nullptr_t) noexcept : pointer_(nullptr) {}
    aligned_ptr(pointer p) noexcept : pointer_(p)
    {
      EVE_ASSERT(is_aligned<Alignment>(p),(void *)(p) << " is not aligned on " << Alignment << ".");
    }

    template<typename U, std::size_t A>
    aligned_ptr(aligned_ptr<U, A> p) noexcept
    requires( (A >= Alignment) && std::convertible_to<U*, pointer> )
    {
      pointer_ = p.get();
    }

    template<typename U, std::size_t A>
    aligned_ptr &operator=(aligned_ptr<U, A> p) noexcept
                requires( (A >= Alignment) && std::convertible_to<U*, pointer> )
    {
      pointer_ = p.get();
      return *this;
    }

    aligned_ptr &operator=(pointer p) noexcept
    {
      assert(is_aligned<Alignment>(p));
      pointer_ = p;
      return *this;
    }

    explicit operator bool() const noexcept { return pointer_ != nullptr; }
    pointer  get() const noexcept { return pointer_; }
    void     swap(aligned_ptr &that) noexcept { std::swap(pointer_, that.pointer_); }

  private:
    pointer pointer_;
  };
  #endif

  //================================================================================================
  //! @brief Checks if an aligned_ptr is aligned on a given alignment.
  //! @param ptr aligned_ptr to checks
  //! @tparam Other Alignment constraint to verify
  //! @return A boolean indicating if `ptr` is compatible with the `Other` alignment.
  //================================================================================================
  template<std::size_t A, typename T, std::size_t Other>
  constexpr bool is_aligned(aligned_ptr<T, Other> const &ptr) noexcept
  {
    if constexpr(A <= Other)  return true;
    else                      return is_aligned(ptr.get());
  }

  //================================================================================================
  //! @}
  //================================================================================================

  template<typename T, std::size_t A> struct element_type<aligned_ptr<T,A>> { using type = T; };
  template<typename T>                struct element_type<aligned_ptr<T>>   { using type = T; };

  template<typename T1, std::size_t A1, typename T2, std::size_t A2>
  bool operator==(aligned_ptr<T1, A1> lhs, aligned_ptr<T2, A2> rhs) noexcept
  {
    return lhs.get() == rhs.get();
  }

  template<typename T, std::size_t A>
  bool operator==(aligned_ptr<T, A> lhs, T* rhs) noexcept
  {
    return lhs.get() == rhs;
  }

  template<typename T, std::size_t A>
  bool operator==(T* lhs, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() == lhs;
  }

  template<typename T, std::size_t A>
  bool operator==(aligned_ptr<T, A> lhs, std::nullptr_t) noexcept
  {
    return lhs.get() == nullptr;
  }

  template<typename T, std::size_t A>
  bool operator==(std::nullptr_t, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() == nullptr;
  }

  template<typename T1, std::size_t A1, typename T2, std::size_t A2>
  bool operator!=(aligned_ptr<T1, A1> lhs, aligned_ptr<T2, A2> rhs) noexcept
  {
    return lhs.get() != rhs.get();
  }

  template<typename T, std::size_t A>
  bool operator!=(aligned_ptr<T, A> lhs, T* rhs) noexcept
  {
    return lhs.get() != rhs;
  }

  template<typename T, std::size_t A>
  bool operator!=(T* lhs, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() != lhs;
  }

  template<typename T, std::size_t A>
  bool operator!=(aligned_ptr<T, A> lhs, std::nullptr_t) noexcept
  {
    return lhs.get() !=nullptr;
  }

  template<typename T, std::size_t A>
  bool operator!=(std::nullptr_t, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get()!= nullptr;
  }

  template<typename Type, std::size_t Alignment>
  void swap(aligned_ptr<Type, Alignment> &lhs, aligned_ptr<Type, Alignment> &rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template<typename Type, std::size_t Alignment>
  aligned_ptr<Type, Alignment> operator-(aligned_ptr<Type, Alignment> const &p,
                                         std::ptrdiff_t                      o) noexcept
  {
    auto that = p;
    return that -= o;
  }

  template<typename Type, std::size_t Alignment>
  aligned_ptr<Type, Alignment> operator+(aligned_ptr<Type, Alignment> const &p,
                                         std::ptrdiff_t                      o) noexcept
  {
    auto that = p;
    return that += o;
  }

  template<typename Type, std::size_t Alignment>
  aligned_ptr<Type, Alignment> operator+(std::ptrdiff_t                      o,
                                         aligned_ptr<Type, Alignment> const &p) noexcept
  {
    auto that = p;
    return that += o;
  }

  //================================================================================================
  //! @relates eve::aligned_ptr
  //!
  //! @brief Constructs an aligned_ptr from a pointer `ptr`.
  //! Behavior is undefined if `ptr` does not satisfy alignment constraint `Alignment`.
  //!
  //! @tparam Alignment Alignment constraint to uphold
  //! @param  ptr       Pointer to wrap
  //! @return An aligned_ptr holding`ptr` with the proper alignment constraint.
  //================================================================================================
  template<std::size_t Alignment, typename Type>
  aligned_ptr<Type, Alignment> as_aligned(Type* ptr) noexcept
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
  template<std::size_t Alignment, typename Type>
  aligned_ptr<Type const, Alignment> as_aligned(Type const *ptr) noexcept
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
  //! SIMD registers of size `Cardinal`.
  //!
  //! @param p      Pointer to realign
  //! @param width  SIMD cardinal to use as alignment constraint
  //! @return An aligned_ptr holding the realigned pointer with the proper alignment constraint.
  //! @see previous_aligned_address(T*)
  //================================================================================================
  template <typename T, typename Cardinal>
  #if !defined(EVE_DOXYGEN_INVOKED)
  EVE_FORCEINLINE auto previous_aligned_address(T* p, Cardinal) noexcept
  #else
  EVE_FORCEINLINE auto previous_aligned_address(T* p, Cardinal width) noexcept
  #endif
  {
    constexpr std::size_t alignment = Cardinal() * sizeof(T);
    return eve::aligned_ptr<T, alignment>{eve::align(p, eve::under{alignment})};
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
  template<typename Type, std::size_t Alignment>
  struct  pointer_alignment<aligned_ptr<Type, Alignment>>
        : std::integral_constant<std::size_t,Alignment>
  {};
}
