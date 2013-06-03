/*
 * Copyright (C) 2006-2012 Music Technology Group (MTG)
 *                         Universitat Pompeu Fabra
 *
 */


#ifndef ESSENTIA_PITCHSALIENCEFUNCTIONPEAKS_H
#define ESSENTIA_PITCHSALIENCEFUNCTIONPEAKS_H

#include "algorithmfactory.h"

namespace essentia {
namespace standard {

class PitchSalienceFunctionPeaks : public Algorithm {

 private:
  Input<std::vector<Real> > _salienceFunction;
  Output<std::vector<Real> > _salienceBins;
  Output<std::vector<Real> > _salienceValues;

  Algorithm* _peakDetection;  

 public:
  PitchSalienceFunctionPeaks() {
    declareInput(_salienceFunction, "salienceFunction", "the array of salience function values corresponding to cent frequency bins");
    declareOutput(_salienceBins, "salienceBins", "the cent bins corresponding to salience function peaks");
    declareOutput(_salienceValues, "salienceValues", "the values of salience function peaks");
    
    _peakDetection = AlgorithmFactory::create("PeakDetection");
  }

  ~PitchSalienceFunctionPeaks() {
    delete _peakDetection;
  }

  void declareParameters() {
    declareParameter("binResolution", "salience function bin resolution [cents]", "(0,inf)", 10.0);
    declareParameter("minFrequency", "the minimum frequency to evaluate (ignore peaks below) [Hz]", "[0,inf)", 55.0);
    declareParameter("maxFrequency", "the maximum frequency to evaluate (ignore peaks above) [Hz]", "[0,inf)", 1760.0);
    declareParameter("referenceFrequency", "the reference frequency for Hertz to cent convertion [Hz], corresponding to the 0th cent bin", "(0,inf)", 55.0);
  }

  void configure();
  void compute();

  static const char* name;
  static const char* version;
  static const char* description;

}; // class PitchSalienceFunctionPeaks

} // namespace standard
} // namespace essentia


#include "streamingalgorithmwrapper.h"

namespace essentia {
namespace streaming {

class PitchSalienceFunctionPeaks : public StreamingAlgorithmWrapper {

 protected:
  Sink<std::vector<Real> > _salienceFunction;
  Source<std::vector<Real> > _salienceBins;
  Source<std::vector<Real> > _salienceValues;

 public:
  PitchSalienceFunctionPeaks() {
    declareAlgorithm("PitchSalienceFunctionPeaks");
    declareInput(_salienceFunction, TOKEN, "salienceFunction");
    declareOutput(_salienceBins, TOKEN, "salienceBins");
    declareOutput(_salienceValues, TOKEN, "salienceValues");
  }
};

} // namespace streaming
} // namespace essentia

#endif // ESSENTIA_PITCHSALIENCEFUNCTIONPEAKS_H