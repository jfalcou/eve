.. _function-is_lez:

######
is_lez
######

**Required header** ``#include <eve/function/is_lez.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_lez = {};
   }

Function object determining if the given :ref:`Value <concept-value>` is less or equal to zero

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is less or equal to zero.
* [2] returns :ref:`True <constant-true_>` if **s** is  less or equal to zero.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

.. rubric:: Notes

* The computation ``is_lez(x)`` is equivalent to ``is_less_equal(x, Zero(as(x)))``


Example
*******

.. include:: ../../../../test/doc/is_lez.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_lez.txt
  :literal:

