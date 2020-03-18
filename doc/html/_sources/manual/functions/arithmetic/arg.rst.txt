.. _function-arg:

###
arg
###

**Required header:** ``#include <eve/function/arg.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ arg = {};
   }

Function object computing argument of a :ref:`IEEEValue <concept-ieeevalue>`.


Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise argument value of the :ref:`IEEEValue <concept-ieeevalue>`.

Parameter 
**********

* ``x`` : Instance of an  :ref:`IEEEValue <concept-ieeevalue>`.

Return value
**************

* A value with the same type as the parameter.

Notes
*******

  -  With the :ref:`pedantic_ <feature-decorator>` decorator this function return a Nan for a Nan entry.

  -  For :ref:`IEEEValue <concept-ieeevalue>` it returns the value zero (if the bit of sign of the entry is not set)
     or the value :math:`\pi` (if it is set).
   
  - Its use will be extended in a future complex module.

Example
*******

.. include:: ../../../../test/doc/core/arg.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/arg.txt
  :literal:
