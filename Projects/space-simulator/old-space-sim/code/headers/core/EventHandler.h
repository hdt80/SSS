#pragma once

#include <core/event_queue.h>

namespace sss {

    struct EventHandler {
        public:
            static void handle_event(const sss_event& evnt);

        private:
            static void handle_set_event(const sss_event& evnt);
            static void handle_get_event(const sss_event& evnt);
            static void handle_evn_event(const sss_event& evnt);
    };

}
