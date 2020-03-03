.. _function-conj:

#######
conj
#######

**Required header:** ``#include <eve/function/conj.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ conj = {};
   }

Function object computing conjugate of an  :ref:`IEEEValue <concept-ieeevalue>`.


Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise conjugate of the :ref:`wide <type-wide>`.
* [2] Computes the conjugate of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Options
*******

Notes
*****

This function coincides with identity on ref:`concept-ieeevalue` and is not defined for :ref:`concept-integralvalue` types.
Its use will be extended in a future complex module. On complex entries `conj` and identity do not coincide.

Example
*******

.. include:: ../../../../test/doc/core/conj.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/conj.txt
  :literal:
