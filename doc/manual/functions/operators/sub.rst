.. _function-sub:

sub
===

**Required header** ``#include <eve/function/sub.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value sub( Value lhs, Value rhs ) noexcept
   }

Function object for performing substarction over two :ref:`concept-value` of the same type.

Parameters
----------

  - ``lhs``, ``rhs`` : values to substract

Return value
------------

The sum of  ``arg0`` and ``arg1`` for every element of each parameters.

Options
-------


Example
-------

.. include:: ../../../../test/doc/sub.cpp
  :literal:

Possible output

.. code-block:: c++

   sub(3.f, 5.5f) = -2.5
   sub(3_wf, {1,2,3,4}) = {2,1,0,-1}

