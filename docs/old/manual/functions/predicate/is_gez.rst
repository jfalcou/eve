.. _function-is_gez:

######
is_gez
######

**Required header** ``#include <eve/function/is_gez.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_gez = {};
   }

Function object determining if the given :ref:`Value <concept-value>` is greater or equal to zero

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is greater or equal to zero.
* [2] returns :ref:`True <constant-true_>` if **s** is  greater or equal to zero.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

.. rubric:: Notes

* The computation ``is_gez(x)`` is equivalent to ``is_greater_equal(x, Zero(as(x)))``


Options
*******


.. seealso::  :ref:`Smallestposval <constant-Smallestposval>`, :ref:`abs <function-abs>`, :ref:`is_less <function-is_less>`, :ref:`is_nez <function-is_nez>`


Example
*******

.. include:: ../../../../test/doc/core/is_gez.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/is_gez.txt
  :literal:

