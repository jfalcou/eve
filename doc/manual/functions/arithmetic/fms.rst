.. _function-fms:

##############
fms
##############

**Required header:** ``#include <eve/function/fms.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ fms = {};
   }

Function object performing a fused-multiply-sub between three :ref:`Values <concept-value>`.


********
Synopsis
********

.. code-block:: c++

   template<typename T,typename U,typename V>  auto operator()( T const& x, U cons & y, V const & z ) noexcept;

* performs element-wise fused multiply-sub of the three parameters

Parameters
**********

* Each parameter must be an :ref:`Ieee Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Value <concept-value>` type.

Return value
**************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

*****
Notes
*****

    The call ``fms(x, y, z)`` is similar to ``x*y-z``

    But really conformant fused-multiply-sub also implies

    - only one rounding

    - nointermediate" overflow

    Our ``fms`` provides this for all :ref:`concept-integralvalue`  types and also each time it is reasonable
    in terms of performance for :ref:`concept-ieeevalue` ones (i.e. if the system has the hard
    wired capability).

    If you need pedantic fms capabilities in all circumstances in your own
    code you can use the :ref:`pedantic_ <feature-decorator>` or :ref:`numeric_ <feature-decorator>` options
    (although it can be very expensive).

*******
Options
*******

    - With the :ref:`pedantic_ <feature-decorator>` decorator: ensures the one rounding property and allows SIMD
      acceleration if available.

    - With the :ref:`numeric_ <feature-decorator>` decorator: ensures the whole fma conformant properties
      and allows SIMD acceleration if available.

*******
Example
*******

.. include:: ../../../../test/doc/core/fms.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/fms.txt
  :literal:
