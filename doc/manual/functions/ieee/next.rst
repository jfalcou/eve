.. _function-next:

####
next
####

**Required header:** ``#include <eve/function/next.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ next = {};
   }

    This function object returns the  (`n`-th if the second parameter is present) least representable
    element strictly greater than the parameter


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>              wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& v, U const & n) noexcept;
   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& v, wide<U,N> const & m) noexcept;
   template<typename T> constexpr T                        operator()( T s ) noexcept;
   template<typename T> constexpr T                        operator()( T s, U n) noexcept;

* [1] Computes the element-wise least representable element strictly greater than the first parameter
* [2] Computes the element-wise  n-th least representable element strictly greater than the first parameter
* [3] Computes the element-wise m-th least representable element strictly greater than the first parameter
* [4] Computes the least representable element strictly greater than the first parameter
* [5] Computes the least  n-th least representable element strictly greater than the first parameter

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,5] A value with the same type as the first parameter.

Notes
******

  - the second parameter elements are to be positive integral values.

  - If the second parameter is 0 the first parameter is returned.

Options
*******

  with :ref:`saturated_ <feature-decorator>` options and integral input ``next(Valmax,n)`` is ``Valmax``

Example
*******

.. include:: ../../../../test/doc/core/next.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/next.txt
  :literal:
