.. _function-is_ltz:

######
is_ltz
######

**Required header** ``#include <eve/function/is_ltz.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_ltz = {};
   }

Function object determining if the given :ref:`Value <concept-value>` is less than zero

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is less than zero.
* [2] returns :ref:`True <constant-true_>` if **s** is  less than zero.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

.. rubric:: Notes

* The computation ``is_ltz(x)`` is equivalent to ``is_less(x, Zero(as(x)))``


Example
*******

.. include:: ../../../../test/doc/core/is_ltz.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/is_ltz.txt
  :literal:

