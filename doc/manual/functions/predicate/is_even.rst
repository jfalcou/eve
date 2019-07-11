.. _function-is_even:

#######
is_even
#######

**Required header** ``#include <eve/function/is_even.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_even = {};
   }

Function object determining if the given :ref:`Value <concept-value>` is even

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is even.
* [2] returns :ref:`True <constant-true_>` if **s** is even.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

Note
*******

* for a :ref:`concept-ieeevalue` value ``x`` to be even means that both ``x`` and ``x/2`` are flint.
Options
*******

Example
*******

.. include:: ../../../../test/doc/is_even.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_even.txt
  :literal:

