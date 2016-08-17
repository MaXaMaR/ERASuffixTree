#pragma once

#include <functional>

#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

class Work {
public:
    using WorkUnit = std::function<void()>;

    Work();
    ~Work();

    boost::asio::io_service ioService;
    boost::asio::io_service::work work;

    boost::thread_group threadpool;
};

extern Work work;
