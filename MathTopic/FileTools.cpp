#include "FileTools.h"

#include <filesystem>
#include <fstream>

bool FileTools::CreateFile(const std::string& file_name) {
	if (std::filesystem::is_regular_file(file_name)) {
		return true;
	}

	std::filesystem::path file_path(file_name);
	std::filesystem::path dir_path = file_path.parent_path();
	if (dir_path.empty()) {
		return false;
	}
	std::error_code err;
	if (!std::filesystem::is_directory(dir_path)) {
		std::filesystem::create_directories(dir_path, err);
		if (err.value() != 0) {
			return false;
		}
	}

	if (!std::filesystem::is_regular_file(file_path)) {
		std::ofstream file(file_name, std::ios::out);
		if (file.is_open()) {
			file.close();
		} else {
			return false;
		}
	}

	return true;
}
