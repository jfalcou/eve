.. _function-is_imag:

################
is_imag
################

**Required header** ``#include <eve/function/is_imag.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ is_imag = {};
   }

Function object returning True if and only if the parameter is zero.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             as_logical_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T            > constexpr   as_logical_t<T>         operator()( T s ) noexcept;

* [1] For each element of **v** returns :ref:`True <constant-true_>` if the element is zero.
* [2] returns :ref:`True <constant-true_>` if **s** is zero.

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

.. include:: ../../../../test/doc/is_imag.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/is_imag.txt
  :literal:

