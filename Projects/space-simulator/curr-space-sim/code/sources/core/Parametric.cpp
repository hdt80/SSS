#include <core/Parametric.h>

namespace sss {
    
    Parametric::Parametric(float max, const std::function<float(float, float)>& Fx, 
                           const std::function<float(float, float)>& Fy, const std::function<float(float, float)>& Fz, float step) 
        : _Fx(Fx), _Fy(Fy), _Fz(Fz) 
    {
        _currIter = 0;
        for(float i = 0.0f; i < max; i += step) {
            for(float j = 0.0f; j < max; j += step) {
                _vals.push_back(std::make_pair(i, j));
            } 
        } 
    }

    glm::vec3 Parametric::next() {
        glm::vec3 result;
        std::pair<float, float> p = _vals[_currIter];
        _currIter = (_currIter == _vals.size() + 1) ? 0 : _currIter + 1;
        result.x = _Fx(p.first, p.second);
        result.y = _Fy(p.first, p.second);
        result.z = _Fz(p.first, p.second);
        return result;
    }

}
