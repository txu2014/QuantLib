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
#include <qlo/evolutiondescription.hpp>
#include <ql/models/marketmodels/multiproduct.hpp>
#include <ql/models/marketmodels/evolutiondescription.hpp>

namespace QuantLibAddin {
    
    EvolutionDescription::EvolutionDescription(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const std::vector<QuantLib::Time>& rateTimes,
            const std::vector<QuantLib::Time>& evolutionTimes,
            bool permanent) : ObjectHandler::LibraryObject<QuantLib::EvolutionDescription>(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::EvolutionDescription>(
            new QuantLib::EvolutionDescription(rateTimes, evolutionTimes));
    }

    EvolutionDescription::EvolutionDescription(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::EvolutionDescription& ev,
            bool permanent) : ObjectHandler::LibraryObject<QuantLib::EvolutionDescription>(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::EvolutionDescription>(
            new QuantLib::EvolutionDescription(ev));
    }

    EvolutionDescription::EvolutionDescription(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const QuantLib::MarketModelMultiProduct& product,
            bool permanent) : ObjectHandler::LibraryObject<QuantLib::EvolutionDescription>(properties, permanent)
    {
        const QuantLib::EvolutionDescription& ev = product.evolution();
        libraryObject_ =
           boost::shared_ptr< QuantLib::EvolutionDescription>(new QuantLib::EvolutionDescription(ev));
    }

}

