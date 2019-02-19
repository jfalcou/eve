.. _function-add:

add
===

**Required header** ``#include <eve/function/add.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr Value add( Value lhs, Value rhs ) noexcept                  // (1)
     constexpr Value operator+( Value lhs, Value rhs ) noexcept            // (2)
   }

(1) Function object for performing addition over two :ref:`concept-value` of the same type.
(2) Infix operator for performing addition over two :ref:`concept-value` of the same type.

Parameters
----------

  - ``lhs``, ``rhs`` : values to sum

Return value
------------

The sum of  ``lhs`` and ``rhs`` for every elements of each parameter.

Options
-------


Example
-------

.. include:: ../../../../test/doc/add.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/add.txt
  :literal:

