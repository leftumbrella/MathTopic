#include "JsonMath.h"
#include <exception>

JsonMath::JsonMath() {

}

JsonMath::~JsonMath() {

}

bool JsonMath::DelPoint(const std::initializer_list<std::string>& keys) {
	if (keys.size() == 0 || _file_path.empty()) {
		return false;
	}
	std::ifstream file;
	file.open(_file_path, std::ios::in);
	if (!file.is_open()) {
		return false;
	}
	nlohmann::json js;
	file >> js;
	file.close();

	nlohmann::json* js_ptr = &js;
	nlohmann::json::iterator find;
	int count = 0;
	for (const auto& key : keys) {
		++count;
		find = js_ptr->find(key);
		if (find == js_ptr->cend()) {
			return false;
		}
		if (count != keys.size()) {
			js_ptr = &*find;
		}
	}
	
	js_ptr->erase(find);

	
	std::fstream file_out;
	file_out.open(_file_path, std::ios::out);
	if (!file_out.is_open()) {
		return false;
	}
	file_out << std::setw(4) << js << std::endl;
	file_out.close();

	return true;
}

JsonMath*  JsonMath::_instance = nullptr;
JsonMath* JsonMath::instance() {
	if (_instance == nullptr) {
		_instance = new JsonMath;
	}
	return _instance;
}

bool JsonMath::SetFile(const std::string& file_name) {
	if (FileTools::CreateFile(file_name)) {
		_file_path = file_name;
		return true;
	}
	return false;
}

bool JsonMath::ReadSubjects(std::vector<std::string>& subjects) {
	return ReadSubjects(subjects, { RootKeyName });
}

bool JsonMath::ReadSubjects(std::vector<std::string>& subjects, const std::initializer_list<std::string>& keys) {
	if (keys.size() == 0 || _file_path.empty()) {
		return false;
	}
	nlohmann::json js_obj;
	std::ifstream file_json;
	file_json.open(_file_path);
	if (!file_json.is_open()) {
		return false;
	}
	js_obj << file_json;
	file_json.close();
	for (auto itr = keys.begin(); itr != keys.end(); ++itr) {
		nlohmann::json::iterator find = js_obj.find(*itr);
		if (find == js_obj.end()) {
			return false;
		}
		js_obj = *find;
	}

	for (auto itr = js_obj.cbegin(); itr != js_obj.cend(); ++itr) {
		subjects.push_back(itr.key());
	}

	return !subjects.empty();
}

bool JsonMath::ReadFormulas(std::vector<FORMULA>& formulas, const std::initializer_list<std::string>& keys) {
	if (keys.size() == 0 || _file_path.empty()) {
		return false;
	}
	nlohmann::json js_obj;
	std::ifstream file_json;
	file_json.open(_file_path);
	if (!file_json.is_open()) {
		return false;
	}
	js_obj << file_json;
	file_json.close();
	for (auto itr = keys.begin(); itr != keys.end(); ++itr) {
		nlohmann::json::iterator find = js_obj.find(*itr);
		if (find == js_obj.end()) {
			return false;
		}
		js_obj = *find;
	}
	
	for (auto itr = js_obj.cbegin(); itr != js_obj.cend(); ++itr) {
		formulas.push_back(Formula2Str(itr.value()));
	}

	return !formulas.empty();
}

bool JsonMath::ReadFormulas(std::vector<FORMULA>& formulas, const std::string& sub_name) {
	return ReadFormulas(formulas, { RootKeyName ,sub_name });
}

bool JsonMath::WriteFormulas(const std::vector<FORMULA>& formulas, const std::initializer_list<std::string>& keys) {
	if (keys.size() == 0 || _file_path.empty()) {
		return false;
	}
	std::vector<std::string> formulas_str;
	for (const auto& formula : formulas) {
		formulas_str.push_back(Formula2Str(formula));
	}
	return WriteFormulas(formulas_str, keys);
}

bool JsonMath::WriteFormulas(const std::vector<std::string>& formulas, const std::initializer_list<std::string>& keys) {
	if (keys.size() == 0 || _file_path.empty()) {
		return false;
	}

	nlohmann::json js_obj;
	std::ifstream file_json;
	file_json.open(_file_path);
	if (!file_json.is_open()) {
		return false;
	}
	try{
		js_obj << file_json;
	}catch (std::exception e){
		js_obj = nlohmann::json();
	}
	
	file_json.close();
	
	nlohmann::json* tmp_json = &js_obj;
	for (const auto& key : keys) {
		tmp_json = &((*tmp_json)[key]);
	}

	tmp_json->clear();
	for (const auto& formula : formulas) {
		tmp_json->push_back(formula);
	}

	std::ofstream file_out;
	file_out.open(_file_path, std::ios::out);
	if (!file_out.is_open()) {
		return false;
	}

	file_out << std::setw(4) << js_obj << std::endl;
	file_out.close();
	return true;
}

bool JsonMath::WriteFormulas(const std::vector<FORMULA>& formulas, const std::string& sub_name) {
	return WriteFormulas(formulas, { RootKeyName ,sub_name });
}

bool JsonMath::WriteFormulas(const std::vector<std::string>& formulas, const std::string& sub_name) {
	return WriteFormulas(formulas, { RootKeyName ,sub_name });
}

FORMULA JsonMath::Formula2Str(const std::string& str) {
	FORMULA formula;
	std::size_t opr_pos = -1;
	if (str.find('+') != -1) {
		opr_pos = str.find('+');
		formula.oper = 1;
	} else if (str.find('-') != -1) {
		opr_pos = str.find('-');
		formula.oper = 2;
	} else if (str.find('*') != -1) {
		opr_pos = str.find('*');
		formula.oper = 3;
	} else if (str.find('/') != -1) {
		opr_pos = str.find('/');
		formula.oper = 4;
	}
	if (opr_pos != -1) {
		formula.left = boost::lexical_cast<int>(str.substr(0, opr_pos));
		std::size_t equal_pos = str.find('=');
		formula.right = boost::lexical_cast<int>(str.substr(opr_pos + 1, equal_pos - opr_pos - 1));
		formula.answer = boost::lexical_cast<int>(str.substr(equal_pos + 1, str.size() - equal_pos - 1));
	}
	return formula;
}

std::string JsonMath::Formula2Str(const FORMULA& formula) {
	std::string over_str;

	over_str += boost::lexical_cast<std::string>(formula.left);
	switch (formula.oper) {
		case 1:	over_str += '+';	break;
		case 2:	over_str += '-';	break;
		case 3:	over_str += '*';	break;
		case 4:	over_str += '/';	break;
		default: return "";
	}
	over_str += boost::lexical_cast<std::string>(formula.right);
	over_str += '=';
	over_str += boost::lexical_cast<std::string>(formula.answer);

	return over_str;
}

bool JsonMath::HaveSubject(const std::string& sub_name) {
	return HaveKeys({ RootKeyName ,sub_name });
}

bool JsonMath::DelSubject(const std::string& sub_name) {
	return DelPoint({ RootKeyName ,sub_name });
}

bool JsonMath::HaveKeys(const std::initializer_list<std::string>& keys) {

	nlohmann::json js_obj;
	std::ifstream file_json;
	file_json.open(_file_path);
	if (!file_json.is_open()) {
		return false;
	}
	js_obj << file_json;
	file_json.close();
	nlohmann::json find = js_obj;
	for (const auto& key : keys) {
		nlohmann::json::iterator value_itr = find.find(key);
		if (value_itr == find.end()) {
			return false;
		}
		find = *value_itr;
	}
	return true;
}
