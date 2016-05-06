/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2006, 2007 Marco Bianchetti
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti

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

#if defined(HAVE_CONFIG_H)     // Dynamically created by configure
    #include <qlo/config.hpp>
#endif
#include <qlo/abcd.hpp>
#include <ql/termstructures/volatility/abcd.hpp>
#include <ql/quotes/simplequote.hpp>
#include <ql/termstructures/volatility/abcdcalibration.hpp>

namespace QuantLibAddin {
   
    AbcdFunction::AbcdFunction(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::Real a, 
            QuantLib::Real b,
            QuantLib::Real c, 
            QuantLib::Real d,
            bool permanent)
    : ObjectHandler::LibraryObject<QuantLib::AbcdFunction>(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::AbcdFunction>(new
            QuantLib::AbcdFunction(a, b, c, d));
    }   

    AbcdCalibration::AbcdCalibration(
               const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
               const std::vector<QuantLib::Time>& times,
               const std::vector<QuantLib::Volatility>& blackVols,
               QuantLib::Real a, QuantLib::Real b,
               QuantLib::Real c, QuantLib::Real d,
               bool aIsFixed, bool bIsFixed,
               bool cIsFixed, bool dIsFixed,
               bool vegaWeighted,
               const boost::shared_ptr<QuantLib::EndCriteria> endCriteria,
               const boost::shared_ptr<QuantLib::OptimizationMethod> method,
               bool permanent)
    : ObjectHandler::LibraryObject<QuantLib::AbcdCalibration>(properties, permanent) {

        libraryObject_ = boost::shared_ptr<QuantLib::AbcdCalibration>(new
            QuantLib::AbcdCalibration(times, blackVols, a, b, c, d,
                                      aIsFixed, bIsFixed, cIsFixed, dIsFixed,
                                      vegaWeighted, endCriteria, method));
    }

}
