.. _function-floor2:

######
floor2
######

**Required header:** ``#include <eve/function/floor2.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ floor2 = {};
   }

Function object computing the greatest power of two value less or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********


.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise greatest power of two values less or equal to the value of the parameter`.

Parameters
**********

* Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Notes
******

  - if the expected result does not exists (input less than one) or is not representable in the parameter type 
    the result is undefined.

Example
*******

.. include:: ../../../../test/doc/core/floor2.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/floor2.txt
  :literal:
