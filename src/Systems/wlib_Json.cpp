//////////////////////////////////////
// (c) 2016  white   wlib_Json
//////////////////////////////////////

#include "wlib_Json.hpp"




//////////////////////////////////////
// Constructors and Destructor
//////////////////////////////////////
wlib::Json::Json(const std::string & json_str)
	: shp_err_str(std::make_shared<std::string>()), first_flag_(true)
{
	//public constructor
	*this->shp_err_str = picojson::parse(this->json_value, json_str);
}

wlib::Json::Json(const picojson::value & v, const std::shared_ptr<std::string> & shp_err_str)
	: json_value(v), shp_err_str(shp_err_str), first_flag_(false)
{
}

wlib::Json::Json(const Json & copy)
	: json_value(copy.json_value), shp_err_str(copy.shp_err_str), first_flag_(copy.first_flag_)
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
	if (this->first_flag_) this->shp_err_str->clear();	//error clear;

	if (!this->failed()) {
		if (this->json_value.is<picojson::object>()) {
			picojson::object tobj = this->json_value.get<picojson::object>();
			if (tobj.count(key) > 0)	return Json(tobj[key], this->shp_err_str);
			else						{ *this->shp_err_str = "No key"; return Json(this->json_value, this->shp_err_str); }
		}
		else							{ *this->shp_err_str = "Not Object"; return Json(this->json_value, this->shp_err_str); }
	}

	//Error
	return *this;
}

wlib::Json wlib::Json::operator[](const std::size_t & index)
{
	if (this->first_flag_) this->shp_err_str->clear();	//error clear;

	if (!this->failed()) {
		if (this->json_value.is<picojson::array>()) {
			picojson::array tarray = this->json_value.get<picojson::array>();
			if (tarray.size() > index)	return Json(tarray.at(index), this->shp_err_str);
			else						{ *this->shp_err_str = "Index Out Of Bounds"; return Json(this->json_value, this->shp_err_str); }
		}
		else							{ *this->shp_err_str = "Not Array"; return Json(this->json_value, this->shp_err_str); }
	}

	//Error
	return *this;
}



/////////////////////////////////////////
// Value Accessor
/////////////////////////////////////////
template<typename T>
T wlib::Json::get(const T & default_val)
{
	if (!this->failed()) {
		if (this->json_value.is<T>()) {
			return this->json_value.get<T>();
		}
		*this->shp_err_str = "Mismatched Type.";
	}
	return default_val;
}

template double wlib::Json::get<double>(const double & default_value);
template bool wlib::Json::get<bool>(const bool & default_flag);
template std::string wlib::Json::get<std::string>(const std::string & default_str);


double wlib::Json::num(const double & default_value)
{
	return this->get<double>(default_value);
}

std::string wlib::Json::str(const std::string & default_str)
{
	return this->get<std::string>(default_str);
}

bool wlib::Json::is(const bool default_flag)
{
	return this->get<bool>(default_flag);
}

std::size_t wlib::Json::size()
{
	if (this->first_flag_) this->shp_err_str->clear();	//error clear;

	if (!this->failed()) {
		if (this->json_value.is<picojson::array>()) {
			picojson::array tarray = this->json_value.get<picojson::array>();
			return tarray.size();
		}
		else { *this->shp_err_str = "Not Array"; return 0; }
	}

	//Error
	return 0;
}


/////////////////////////////////////////
// Error
/////////////////////////////////////////

bool wlib::Json::failed(std::string * message = nullptr) const
{
	if (this->shp_err_str) {
		if (message != nullptr) *message = *this->shp_err_str;
		return !this->shp_err_str->empty();
	}
	else if (message != nullptr) *message = "";
	return false;
}




