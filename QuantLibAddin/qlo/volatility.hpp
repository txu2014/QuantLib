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

#ifndef qla_volatility_hpp
#define qla_volatility_hpp

#include <oh/libraryobject.hpp>

#include <ql/types.hpp>

namespace QuantLib {
    class LmVolatilityModel;
    class PiecewiseConstantVariance;
}

namespace QuantLibAddin {
        
    // Volatility Model
    OH_LIB_CLASS(LmVolatilityModel, QuantLib::LmVolatilityModel);

    OH_OBJ_CLASS(LmLinearExponentialVolatilityModel, LmVolatilityModel);

    class LmExtLinearExponentialVolModel : public LmLinearExponentialVolatilityModel {
    public:
        LmExtLinearExponentialVolModel(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                       const std::vector<QuantLib::Time>& fixingTimes,
                                       QuantLib::Real a,
                                       QuantLib::Real b,
                                       QuantLib::Real c,
                                       QuantLib::Real d,
                                       bool permanent);

    };

    OH_LIB_CLASS(PiecewiseConstantVariance, QuantLib::PiecewiseConstantVariance);

    class PiecewiseConstantAbcdVariance : public PiecewiseConstantVariance {
      public:
        PiecewiseConstantAbcdVariance(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                      QuantLib::Real a, QuantLib::Real b,
                                      QuantLib::Real c, QuantLib::Real d,
                                      const QuantLib::Size resetIndex,
                                      const std::vector<QuantLib::Time>& rateTimes,
                                      bool permanent);

    };  
}

#endif

