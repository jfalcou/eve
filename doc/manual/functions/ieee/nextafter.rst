.. _function-nextafter:

#########
nextafter
#########

**Required header:** ``#include <eve/function/nextafter.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ nextafter = {};
   }

    This function object called with x and y returns the  next representable value of x in the
    direction of y. If x equals y, or y is Nan then x is returned.


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& x, wide<T,N> const& y) noexcept;
   template<typename T, typename U, typename N>  wide<T,N> operator()( wide<T,N> const& x, T z) noexcept;
   template<typename T> constexpr T                        operator()( T s, T z) noexcept;

* [1] Computes the element_wise next representable value of x in the direction of y. If x equals y, then x is returned.
* [2] Computes the element_wise next representable value of x in the direction of z. If x equals y, then x is returned.
* [3] Computes the next representable value of s in the direction of z. If x equals z, then s is returned.
.. rubric:: Parameters

* **x**, **y**: Instance of :ref:`type-wide`.
* **s**, **z**: Scalar value.

.. rubric:: Return value

* [1,3] A value with the same type as the first parameter.

Notes
******

  - A ``pedantic_`` version ensures that if the second parameter is a Nan a Nan is returned to fit to the standard behaviour.

Example
*******

.. include:: ../../../../test/doc/core/nextafter.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/nextafter.txt
  :literal:
