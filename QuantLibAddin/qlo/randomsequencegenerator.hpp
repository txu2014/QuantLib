/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006 Ferdinando Ametrano
 Copyright (C) 2006 Aurelien Chanudet

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

#ifndef qla_randomsequencegenerator_hpp
#define qla_randomsequencegenerator_hpp

#include <oh/libraryobject.hpp>

#include <ql/math/randomnumbers/rngtraits.hpp>
#include <ql/math/randomnumbers/faurersg.hpp>
#include <ql/math/randomnumbers/mt19937uniformrng.hpp>
#include <ql/math/randomnumbers/sobolrsg.hpp>
#include <ql/math/randomnumbers/haltonrsg.hpp>

#include <vector>

namespace QuantLibAddin {


    QuantLib::Real rand();
    void randomize(QuantLib::BigNatural seed);

    class RandomSequenceGenerator : public ObjectHandler::Object {
      public:
        std::vector<std::vector<double> > variates(long samples);
        virtual std::vector<double> nextSequence() const = 0;
      protected:
        OH_OBJ_CTOR(RandomSequenceGenerator, ObjectHandler::Object);
    };

    // Pseudo Random Sequences

    template <class URNG>
    class PseudoRandomSequenceGenerator : public RandomSequenceGenerator {
      public:
        PseudoRandomSequenceGenerator(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            long dimension, 
            const URNG& urng,
            bool permanent)
      : RandomSequenceGenerator(properties, permanent),
        ursg_(QuantLib::RandomSequenceGenerator<URNG>(dimension, urng)) {}

        virtual std::vector<QuantLib::Real> nextSequence() const {
            return ursg_.nextSequence().value;
        }

      private:
        typename QuantLib::GenericPseudoRandom<URNG, QuantLib::InverseCumulativeNormal>::ursg_type ursg_;
    };

    class MersenneTwisterRsg : public PseudoRandomSequenceGenerator<QuantLib::MersenneTwisterUniformRng> {
      public:
        typedef QuantLib::MersenneTwisterUniformRng urng_type;

        MersenneTwisterRsg(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            long dimension,
            long seed,
            bool permanent);
    };

    // Low Discrepancy Sequences

    template <class URSG>
    class LowDiscrepancySequenceGenerator : public RandomSequenceGenerator {
      public:
        LowDiscrepancySequenceGenerator(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const URSG& ursg,
            bool permanent) 
            : RandomSequenceGenerator(properties, permanent), ursg_(ursg) {}

        virtual std::vector<double> nextSequence() const {
            return ursg_.nextSequence().value;
        }

      private:
        typename QuantLib::GenericLowDiscrepancy<URSG, QuantLib::InverseCumulativeNormal>::ursg_type ursg_;
    };

    class FaureRsg : public LowDiscrepancySequenceGenerator<QuantLib::FaureRsg> {
      public:
        typedef QuantLib::FaureRsg rsg_type;
        FaureRsg(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            long dimension,
            bool permanent);
    };

    class HaltonRsg : public LowDiscrepancySequenceGenerator<QuantLib::HaltonRsg> {
      public:
        typedef QuantLib::HaltonRsg rsg_type;
        HaltonRsg(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            long dimension,
            long seed,
            bool permanent);
    };

    class SobolRsg : public LowDiscrepancySequenceGenerator<QuantLib::SobolRsg> {
      public:
        typedef QuantLib::SobolRsg rsg_type;
        SobolRsg(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            long dimension,
            long seed,
            bool permanent);
    };

}

#endif

