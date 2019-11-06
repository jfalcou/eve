.. _function-sub:

###
sub
###

**Required header:** ``#include <eve/function/sub.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sub = {};
   }

Function object computing the difference of two :ref:`Values <concept-value>`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T> constexpr               T         operator()( T s, T t ) noexcept;

* [1] Computes the element-wise difference of every elements of both :ref:`type-wide`.
* [2,3] Computes the difference of the scalar with each element of the wide instance.
* [4] Computes the difference of both scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide`.
* **s**, **t**: Scalar values of type **U** convertible to **T**.

.. rubric:: Return value

* [1-3] A value with the same type as the :ref:`type-wide` parameter.
* [4] A value of type **T**.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/sub.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sub.txt
  :literal:
