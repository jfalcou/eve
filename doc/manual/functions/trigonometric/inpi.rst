.. _function-inpi:

####
inpi
####

**Required header:** ``#include <eve/function/inpi.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ inpi = {};
   }

Function object computing the  multiplication  of a :ref:`Value <concept-value>` by the inverse of :math:`\pi`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  multiplication of the :ref:`wide <type-wide>` by the inverse of :math:`\pi`.
* [2] Computes the  multiplication of the scalar by the inverse of :math:`\pi`.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. *TODO*


.. seealso::  :ref:`deginrad <function-deginrad>`

Example
*******

.. include:: ../../../../test/doc/core/inpi.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/inpi.txt
  :literal:
