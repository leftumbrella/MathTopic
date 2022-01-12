#pragma once

#include <string>
#include <Json/json.hpp>
#include <sstream>
#include <iomanip>
#include <initializer_list>
#include "FileTools.h"
#include <boost/lexical_cast.hpp>
#include <fstream>
#include "MathTopicStructs.h"

const std::string RootKeyName = "MathSubjects";

class JsonMath {
public:
	static JsonMath* instance();
	bool SetFile(const std::string& file_name);

	bool ReadSubjects(std::vector<std::string>& subjects);

	bool ReadFormulas(std::vector<FORMULA>& formulas, const std::string& sub_name);
	bool WriteFormulas(const std::vector<FORMULA>& formulas, const std::string& sub_name);
	bool WriteFormulas(const std::vector<std::string>& formulas, const std::string& sub_name);

	FORMULA Formula2Str(const std::string& str);
	std::string Formula2Str(const FORMULA& formula);

	bool HaveSubject(const std::string& sub_name);

	bool DelSubject(const std::string& sub_name);

private:
	JsonMath();
	~JsonMath();
	bool DelPoint(const std::initializer_list<std::string>& keys);

	bool HaveKeys(const std::initializer_list<std::string>& keys);

	bool ReadSubjects(std::vector<std::string>& subjects, const std::initializer_list<std::string>& keys);

	bool ReadFormulas(std::vector<FORMULA>& formulas, const std::initializer_list<std::string>& keys);
	bool WriteFormulas(const std::vector<FORMULA>& formulas, const std::initializer_list<std::string>& keys);
	bool WriteFormulas(const std::vector<std::string>& formulas, const std::initializer_list<std::string>& keys);

	static JsonMath* _instance;
	std::string _file_path;
};

