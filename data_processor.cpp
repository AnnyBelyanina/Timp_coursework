#include "data_processor.h"

double DataProcessor::calculateMean(const std::vector<double>& vec) const {
    if (vec.empty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (double value : vec) {
        sum += value;
    }
    
    // При переполнении double автоматически вернет +inf или -inf
    return sum / vec.size();
}
