.. _function-is_pow2:

###########
is_pow2
###########

**Required header** ``#include <eve/function/is_pow2.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_pow2 = {};
   }

Function object determining if the given :ref:`IEEEValue <concept-ieeevalue>` is a power of 2.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is a power of 2.
* [2] returns :ref:`True <constant-true_>` if **s** is a power of 2.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1] A value of type **as_logical_t<wide<T,N>>**.
* [2] A value of type **as_logical_t<T>**.

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/is_pow2.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/is_pow2.txt
  :literal:

