#pragma once

#include <cmath>
#include <glm/glm.hpp>
#include <functional>
#include <vector>
#include <utility>

namespace sss {
    

    class Parametric {
        private:

            size_t _currIter;
            std::vector<std::pair<float, float>> _vals;

            std::function<float(float, float)> _Fx;
            std::function<float(float, float)> _Fy;
            std::function<float(float, float)> _Fz;

        public:
           
            Parametric(float max, const std::function<float(float, float)>&, 
                    const std::function<float(float, float)>&, const std::function<float(float, float)>&, float step=0.1f); 

            glm::vec3 next();

        private:

    
    };

}
