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

   template<typename T> constexpr T operator()( T x ) noexcept;

*  Computes the element-wise conjugate value of the :ref:`IEEEValue <concept-ieeevalue>`.

Parameters
**********

* Instance of a  :ref:`IEEEValue <concept-ieeevalue>`.

Return value
**************

* A value with the same type as the parameter.

Notes
*****

  - This function coincides with identity on ref:`concept-ieeevalue` and is not defined for :ref:`concept-integralvalue` types.

  - Its use will be extended in a future complex module. On complex entries `conj` and identity do not coincide.

Example
*******

.. include:: ../../../../test/doc/core/conj.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/conj.txt
  :literal:
