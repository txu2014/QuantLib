
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

#ifndef qlxl_conversions_scalartooper_hpp
#define qlxl_conversions_scalartooper_hpp

#include <oh/ohdefines.hpp>
#include <xlsdk/xlsdkdefines.hpp>
#include <ql/time/date.hpp>
#include <ql/interestrate.hpp>

// Override functions in the ObjectHandler namespace

namespace ObjectHandler {

    void scalarToOper(const QuantLib::InterestRate &value, OPER &xScalar, bool dllToFree = true, bool expandVector = true);
    void scalarToOper(const QuantLib::Date &value, OPER &xScalar, bool dllToFree = true, bool expandVector = true);
    void scalarToOper(const QuantLib::Frequency &value, OPER &xScalar, bool dllToFree = true, bool expandVector = true);

    // QuantLib::Real is processed differently than double, but for the compiler the 2 types are synonymous
    // so we cannot override scalarToOper().  For now we implement scalarToOper2() and customize gensrc accordingly.
    void scalarToOper2(const QuantLib::Real &value, OPER &xScalar);

}

#endif
