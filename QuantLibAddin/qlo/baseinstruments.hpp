/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2005 Plamen Neykov

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

#ifndef qla_baseinstruments_hpp
#define qla_baseinstruments_hpp

#include <oh/libraryobject.hpp>

namespace QuantLib {
    class Instrument;
}

namespace QuantLibAddin {
    
    class PricingEngine;
    
    //OH_LIB_CLASS(Instrument, QuantLib::Instrument);
    class Instrument : public ObjectHandler::LibraryObject<QuantLib::Instrument> {
      public:
        void setPricingEngine(boost::shared_ptr<PricingEngine>& e) const;
      protected:
        OH_LIB_CTOR(Instrument, QuantLib::Instrument)
    };

    OH_OBJ_CLASS(OneAssetOption, Instrument);

}

#endif
