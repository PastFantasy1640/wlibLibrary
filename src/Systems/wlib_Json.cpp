//////////////////////////////////////
// (c) 2016  white   wlib_Json
//////////////////////////////////////

#include "wlib_Json.hpp"




//////////////////////////////////////
// Constructors and Destructor
//////////////////////////////////////
wlib::Json::Json(const std::string & json_str, std::string * message)
	: err_str_("")
{
	//public constructor
	this->err_str_ = picojson::parse(this->json_value, json_str);
	if (message != nullptr) *message = this->err_str_;
}

wlib::Json::Json(const picojson::value & v, const std::string & err_str)
	: json_value(v), err_str_(err_str)
{
}

wlib::Json::Json(const Json & copy)
	: json_value(copy.json_value), err_str_(copy.err_str_)
{
}

wlib::Json::~Json()
{
}

///////////////////////////////////////
// Object Accessor
///////////////////////////////////////
wlib::Json wlib::Json::operator[](const std::string & key)
{
	if (!this->failed()) {
		if (this->json_value.is<picojson::object>()) {
			picojson::object tobj = this->json_value.get<picojson::object>();
			if (tobj.count(key) > 0)	return Json(tobj[key], this->err_str_);
			else						return Json(this->json_value, "No Key");
		}
		else							return Json(this->json_value, "Not Object");
	}

	//Error
	return *this;
}

wlib::Json wlib::Json::operator[](const std::size_t & index)
{
	if (!this->failed()) {
		if (this->json_value.is<picojson::array>()) {
			picojson::array tarray = this->json_value.get<picojson::array>();
			if (tarray.size() > index)	return Json(tarray.at(index), this->err_str_);
			else						return Json(this->json_value, "Index Out Of Bounds");
		}
		else							return Json(this->json_value, "Not Array");
	}

	//Error
	return *this;
}

/////////////////////////////////////////
// Value Accessor
/////////////////////////////////////////
template<typename T>
T wlib::Json::get(const T & default_val, std::string * error_message) const
{
	if (!this->failed()) {
		if (this->json_value.is<T>()) {
			return this->json_value.get<T>();
		}
		if(error_message != nullptr) *error_message = "Mismatched Type.";
	}
	else if (error_message != nullptr) *error_message = this->err_str_;
	return default_val;
}

template double wlib::Json::get<double>(const double & default_value, std::string * error_message) const;
template bool wlib::Json::get<bool>(const bool & default_flag, std::string * error_message) const;
template std::string wlib::Json::get<std::string>(const std::string & default_str, std::string * error_message) const;


double wlib::Json::num(const double & default_value, std::string * error_message) const
{
	return this->get<double>(default_value, error_message);
}

std::string wlib::Json::str(const std::string & default_str, std::string * error_message) const
{
	return this->get<std::string>(default_str, error_message);
}

bool wlib::Json::is(const bool default_flag, std::string * error_message) const
{
	return this->get<bool>(default_flag, error_message);
}

std::size_t wlib::Json::size(std::string * error_message) const
{
	if (!this->failed()) {
		if (this->json_value.is<picojson::array>()) {
			picojson::array tarray = this->json_value.get<picojson::array>();
			return tarray.size();
		}
		if (error_message != nullptr) *error_message = "Not Array";
	}
	else if (error_message != nullptr) *error_message = this->err_str_;

	//error return
	return 0;
}


/////////////////////////////////////////
// Error
/////////////////////////////////////////

bool wlib::Json::failed(std::string * message) const
{
	if (message != nullptr) *message = this->err_str_;
	return !this->err_str_.empty();
}




