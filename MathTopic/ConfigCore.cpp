#include "ConfigCore.h"

ConfigCore* ConfigCore::_instance = nullptr;
ConfigCore* ConfigCore::instance() {
	if (_instance==nullptr) {
		_instance = new ConfigCore;
	}
	return _instance;
}

void ConfigCore::SetPath(const std::string& path_str) {
	_path_str = path_str;
	boost::filesystem::path config_path(_path_str);
	if (!boost::filesystem::is_directory(config_path)) {
		boost::filesystem::create_directories(config_path);
	}
	_path_str = _path_str + "/" + CONFIG_NAME;
}

std::string ConfigCore::ReadValue(const char* key_str ,...) {
	std::ifstream file;
	file.open(_path_str ,std::ios::in);
	if (!file.is_open()) {
		return "";
	}
	nlohmann::json js;
	file >> js;
	file.close();

	va_list arg_ptr;
	va_start(arg_ptr ,key_str);
	std::string over_str;
	nlohmann::json key_json = js;
	while (key_str!=nullptr) {
		nlohmann::json::const_iterator find = key_json.find(key_str);
		if (find==key_json.cend()) {
			va_end(arg_ptr);
			return "";
		}
		key_json = *find;
		key_str = va_arg(arg_ptr ,const char*);
	}
	va_end(arg_ptr);
	if (key_json.type()!=nlohmann::detail::value_t::string) {
		return boost::lexical_cast<std::string>(key_json);
	} else {
		return key_json;
	}
}

ConfigCore::ConfigCore() {

}

ConfigCore::~ConfigCore() {

}
