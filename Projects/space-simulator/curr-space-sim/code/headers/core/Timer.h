#pragma once

#include <ctime>

namespace sss {


    class Timer {
        private:
            std::clock_t _start;
            std::clock_t _duration;

        public:
            /**
             * @param duration - given in milliseconds
             */
            Timer(long duration);
            ~Timer();

            double elapsed();
            bool finished();
            void restart();

        protected:
    };

}
