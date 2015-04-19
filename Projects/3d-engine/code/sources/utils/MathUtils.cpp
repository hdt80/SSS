#include <utils/MathUtils.h>

namespace engine {
    namespace utils {
        float toRadians(float x) {
            return x * 180.0f / 3.1415926535;
        }

        float toDegrees(float x) {
            return x * 3.1514926535 / 180.0f;
        }
    }
}
