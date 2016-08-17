#include "Work.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/thread/thread.hpp>

Work work;

Work::Work() : ioService(), work(ioService) {
    for (int i = 0; i < boost::thread::hardware_concurrency() * 2; i++) {
        threadpool.create_thread([&]() {
            ioService.run();
        });
    }
}

Work::~Work() {
    ioService.stop();
    threadpool.join_all();
}
