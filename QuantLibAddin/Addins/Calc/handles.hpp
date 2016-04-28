
/*  
 Copyright (C) 2006, 2007 Eric Ehlers
 
 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// This file was generated automatically by gensrc.py.  If you edit this file
// manually then your changes will be lost the next time gensrc runs.

// This source code file was generated from the following stub:
//      gensrc/gensrc/stubs/stub.calc.category

#ifndef ql_calc_handles_hpp
#define ql_calc_handles_hpp

    STRING SAL_CALL qlHandleCurrentLink(
        const STRING &ObjectId,
        const ANY &Trigger) throw(RuntimeException);

    sal_Int32 SAL_CALL qlHandleEmpty(
        const STRING &ObjectId,
        const ANY &Trigger) throw(RuntimeException);

    sal_Int32 SAL_CALL qlRelinkableHandleLinkTo(
        const STRING &ObjectId,
        const ANY &CurrentLink,
        const ANY &Trigger) throw(RuntimeException);



#endif

