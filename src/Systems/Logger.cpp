#include "Logger.hpp"

#include <iomanip>
#include <thread>
#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <fstream>
#include <mutex>

//STATICAL VARIABLE DECLARATION
namespace {
	std::mutex _mutex;
};

#ifdef _DEBUG
	constexpr wlib::Logger::LogLevel kDefaultLogLevel = wlib::Logger::kAll;
#else
	constexpr wlib::Logger::LogLevel kDefaultLogLevel = wlib::Logger::kErrorOnly;
#endif
wlib::Logger::LogLevel wlib::Logger::log_level_ = kDefaultLogLevel;

//### inline functions ###
wlib::Logger::Logger(const std::string & tag, bool is_output_stdio, bool is_output_file)
	: tag_(tag), is_output_stdio_(is_output_stdio), is_output_file_(is_output_file) {
}

wlib::Logger::~Logger() {
	//Nothing to do.
}

void wlib::Logger::information(const std::string & text) {
	if (this->log_level_ == kAll) this->_write("INFO", text);
}

void wlib::Logger::warning(const std::string & text) {
	if (this->log_level_ <= kWarningAndError) this->_write("WARN", text);
}

void wlib::Logger::error(const std::string & text) {
	if (this->log_level_ <= kErrorOnly) this->_write("ERRO", text, true);
}

void wlib::Logger::changeLogLevel(LogLevel log_level) {
	//for thread safe, lock with mutex
	std::lock_guard<std::mutex> lock(_mutex);
	this->log_level_ = log_level;
}

void wlib::Logger::_write(const std::string & status, const std::string & text, const bool is_cerr = false){
	//[status] Thread:(thread_no) 2017-10-15 03:47:24 <tag> | [text]
	//______________________________________________________| [multi text]

	//error check
	if (text.empty() || status.empty()) return;

	//multi line text split
	std::vector<std::string> multiline_text;
	std::string line_text("");
	std::stringstream ss{ text };
	while (std::getline(ss, line_text, '\n')) {
		multiline_text.push_back(line_text);
	}

	//get the now date and time
	time_t now = std::time(nullptr);
	struct tm* local_now = std::localtime(&now);

	//formatting status string
	std::stringstream status_text_sstream;
	status_text_sstream << status << " Thread:" << std::setw(8) << std::left << std::this_thread::get_id() << " ";
	status_text_sstream << (local_now->tm_year + 1900) << "-"  << std::right << std::setfill('0') << std::setw(2) << (local_now->tm_mon + 1) << "-" << std::setfill('0') << std::setw(2) << local_now->tm_mday << " ";
	status_text_sstream << std::setfill('0') << std::setw(2) << local_now->tm_hour << ":" << std::setfill('0') << std::setw(2) << local_now->tm_min << ":" << std::setw(2) << std::setfill('0') << local_now->tm_sec << " ";
	if(15 - this->tag_.size() > 0) status_text_sstream << std::setw(15 - this->tag_.size()) << std::setfill(' ') << " ";
	status_text_sstream << "<" << this->tag_ << "> ";

	//generate output strings
	const std::string status_text(status_text_sstream.str());
	const std::string space_str(status_text_sstream.str().size(), ' ');
	std::string output_text;
	
	for (auto line_text_p = multiline_text.begin(); line_text_p != multiline_text.end(); ++line_text_p) {
		if (output_text.empty()) output_text.append(status_text);
		else output_text.append("\n" + space_str);
		output_text.append("| " + *line_text_p);
	}

	//for thread safe, lock with mutex
	{
		std::lock_guard<std::mutex> lock(_mutex);

		//open the log file.
		if (this->is_output_file_) {
			std::ofstream output_file_stream(Logger::kLogFilename, std::ios::app);
			if (output_file_stream) output_file_stream << output_text << std::endl;
		}

		//write down to standard io
		if (this->is_output_stdio_) {
			if (is_cerr) std::cerr << output_text << std::endl;
			else std::cout << output_text << std::endl;
		}
	}
}
