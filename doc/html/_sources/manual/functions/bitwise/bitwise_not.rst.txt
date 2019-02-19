.. _function-bitwise_not:

bitwise_not
===========

**Required header** ``#include <eve/function/bitwise_not.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value bitwise_not( Value lhs ) noexcept
   }

Function object for performing bitwise not over a :ref:`Value <concept-value>`, (~lhs)

The result type is the one of the parameter.

Operator notation can be used with operator '~' except in scalar mode if 
operand is floating point because of C++ limitations.


Parameters
----------

  - ``lhs`` : input value

Return value
------------

The bitwise complement of  ``lhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/bitwise_not.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/bitwise_not.txt
  :literal:

