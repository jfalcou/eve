.. _function-is_nez:

######
is_nez
######

**Required header** ``#include <eve/function/is_nez.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_nez = {};
   }

Function object determining if the given :ref:`Value <concept-value>` is not equal to zero

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is not equal to zero.
* [2] returns :ref:`True <constant-true_>` if **s** is  not equal to zero.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

.. rubric:: Notes

* The computation ``is_nez(x)`` is equivalent to ``is_not_equal(x, Zero(as(x)))``


Example
*******

.. include:: ../../../../test/doc/core/is_nez.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/is_nez.txt
  :literal:

