#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <queue>
#include <filesystem>
#include <chrono>
#include <source_location>

namespace Log 
{
	enum LogLevel
	{
		DEBUG = 0,			// ����� ������ �α�
		INFO,				// ������ �޽��� �α�
		WARN,				// ��� �޽��� �α�
		ERROR,				// ���� �޽��� �α�
		FATAL,				// ���� �ɰ��� ���� �޽��� �α�
		LogLevelCnt,
	};

	typedef struct LogMsg
	{
		LogLevel level;
		std::string funcName;
		std::string timestamp; //YYYY - MM - DD - HH-MM
		std::string logmsg;
	}LogMsg;

	class Logger
	{
	private:
		std::thread					loggerLoop_;
		std::mutex					loggerlock_;
		std::condition_variable		queueCondVar_;
		bool						isRunning_;

		std::string					rootdir_;


		std::queue<LogMsg>			LogQueue_;

		bool						showConsole_;

		//---------------------------------------------private Fuctins
		void						loggerLoop();

		std::string					getCurrentDate();
		std::string					getCurrentTime();
		std::string					getTimestamp();

		std::string					levelToString(const LogLevel level);

	public:
		Logger(std::string rootdir, bool showConsole = false);
		~Logger();

		bool Log(const LogLevel level , const std::string msg, const std::source_location& loc = std::source_location::current());
	};
}

