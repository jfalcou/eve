.. _function-copysign:

########
copysign
########

**Required header:** ``#include <eve/function/copysign.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ copysign = {};
   }

Function object computing the first  :ref:`Values <concept-value>` with the sign of the second.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T> constexpr               T         operator()( T s, T t ) noexcept;

* [1] Returns an element-wise copy of the sign of the second  :ref:`wide <type-wide>` to the first one.
* [2] Returns an element-wise copy of the sign of the second prameter to  the first one.
* [3] Returns an element-wise copy of the signs of the second prameter to the first one.
* [4] Returns the first parameter with the sign of the second.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**, **t**: Scalar values of type **U** which must be convertible to **T**.

.. rubric:: Return value

* [1-3] A value with the same type as the :ref:`type-wide` parameter.
* [4] A value of type **T**.

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/copysign.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/copysign.txt
  :literal:
