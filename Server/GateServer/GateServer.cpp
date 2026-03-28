#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "CServer.h"
#include "ConfigMgr.h"
#include "RedisMgr.h"


int main()
{
	auto& gCfgMgr = ConfigMgr::Inst();
	std::string gate_port_str = gCfgMgr["GateServer"]["Port"];
	unsigned short gate_port = atoi(gate_port_str.c_str());
	try {
		unsigned short port = static_cast<unsigned short>(8080);
		net::io_context ioc{ 1 };
		/*
			signal_set: 创建一个异步信号集，监听两个特定的操作系统信号：
			SIGINT: 用户按下 Ctrl+C 时触发。
			SIGTERM: 系统发送的终止请求（如 kill 命令）。
			async_wait: 注册一个回调函数。当接收到上述任一信号时，Asio 会异步调用这个 lambda 表达式。
		*/
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {
			if (error) {
				return;
			}
			//它不会立即杀死进程，而是让 ioc.run() 方法在完成当前正在处理的任务后尽快返回。
			ioc.stop();
			});
		std::make_shared<CServer>(ioc, port)->Start();
		std::cout << "Gate Server listen on port: " << port << std::endl;
		//事件驱动: run() 方法会不断从内部队列中取出就绪的事件
		ioc.run();
	}
	catch (std::exception const& e) {
		std::cerr << "Error" << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}