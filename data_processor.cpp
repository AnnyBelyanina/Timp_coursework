/** @file
 * @author Белянина А.А.
 * @version 1.0
 * @date 22.11.2026
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 * @brief Реализация модуля обработки данных
 */
 
#include "data_processor.h"

double DataProcessor::calculateMean(const std::vector<double>& vec) const {
    // обработка граничного случая: пустой вектор
    if (vec.empty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    // накопление суммы элементов вектора
    for (double value : vec) {
        sum += value;
    }
    // вычисление среднего арифметического
    // При переполнении тип double автоматически вернет +inf или -inf
    return sum / vec.size();
}
