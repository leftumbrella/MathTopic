#ifndef LFTUBRLA_CORE_CONFIGCORE_H_
#define LFTUBRLA_CORE_CONFIGCORE_H_

#include <Json/json.hpp>
#include <fstream>
#include <iomanip>
#include "FileTools.h"
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

class ConfigCore {
public:
	static ConfigCore* instance();
	bool SetPath(const std::string& path_str);
	std::string ReadValue(const char* key_str ,...);
	template <typename T> bool SetValue(const T& value ,const char* key_str ,...);
private:
	ConfigCore();
	~ConfigCore();
private:
	static ConfigCore* _instance;
	std::string _path_str;
};

template <typename T> bool ConfigCore::SetValue(const T& value ,const char* key_str ,...) {
	std::fstream file;
	if (!boost::filesystem::is_regular_file(_path_str)) {
		file.open(_path_str, std::ios::out);
		if (file.is_open()) {
			file.close();
		}
	}
	file.open(_path_str ,std::ios::in);
	if (!file.is_open()) {
		return false;
	}

	nlohmann::json js_obj;
	try {
		file >> js_obj;
	} catch (const std::exception&) {
		file.close();
		js_obj = nlohmann::json();
	}
	file.close();

	va_list arg_ptr;
	va_start(arg_ptr ,key_str);
	nlohmann::json* tmp_json = &js_obj;
	while (key_str!=nullptr) {
		tmp_json = &((*tmp_json)[key_str]);
		key_str = va_arg(arg_ptr ,const char*);
	}
	file.open(_path_str ,std::ios::out);
	if (!file.is_open()) {
		va_end(arg_ptr);
		return false;
	}
	*tmp_json = value;
	file << std::setw(4) << js_obj << std::endl;
	file.close();
	va_end(arg_ptr);

	return true;
}

#endif