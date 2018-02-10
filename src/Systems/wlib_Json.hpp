////////////////////////////////////////
//(c) 2016  white    wlib_Json.hpp
////////////////////////////////////////

#pragma once
#ifndef WLIB_JSON_HPP
#define WLIB_JSON_HPP

#include <string>
#include <memory>
#include "picojson.hpp"

namespace wlib {

/**
 * Json�t�@�C���̓��o�̓N���X�ł��B�O�����C�u����picojson�Ɉˑ����Ă��āApicojson�̃��b�p�[�N���X�ƂȂ��Ă��܂��B
 * �g�����͔��ɃV���v���ł��Bphp�̉��z�z��̂悤�ɂȂ��Ă܂��̂ŁA�L�[���[�h�������珇�Ɏw�肵�Ă����邾���œǂݍ��݂��ł��܂��B
 * @version 0.2(�������ݖ�����)
 * @author S.Shirao
 */
class Json {
public:

	/** �R���X�g���N�^
	 * �R���X�g���N�^��json�e�L�X�g���󂯕t���A�f�R�[�h���s���܂��B�f�R�[�h�Ɏ��s�����ꍇ�Ajson�C���X�^���X�͐�������܂��������Ȃ�ǂݍ��݂ɂ����s���܂��B�܂��Afailed�֐����g�����ƂŁA�ǂݍ��݂Ɏ��s�������ǂ����킩��܂��B
	 * Json�N���X�ł́A�Ⴆ�΃t�@�C������̓ǂݍ��݊֐��Ȃǂ͎������Ă��܂���B�K�������t�@�C������ǂݍ��ނ̂����ׂĂł͂Ȃ�����ł��B
	 * @param json_str json�e�L�X�g
	 */
	explicit Json(const std::string & json_str, std::string * message = nullptr);

	/** �f�X�g���N�^
	 * ���̂Ƃ���NOP�ł��B
	 */
	virtual ~Json();

	/** �q�v�f�փA�N�Z�X���܂��B
	 * @param key �L�[������
	 * @returns wlib::Json �q�����[�g�Ƃ���Json�c���[
	 */
	Json operator[](const std::string & key);

	/** Access the json array in index
	 * @param index the index of the json array.
	 * @returns wlib::Json Instance
	 */
	Json operator[](const std::size_t & index);

	//Json at(const std::string & key) const;
	//Json at(const std::size_t & index) const;

	/** ���̗v�f�𐔒l�Ƃ��ēǂݏo���܂��B
	 * @param default_value �ǂݍ��݂Ɏ��s�����ꍇ�ɂ͂��̐��l�����̂܂ܖ߂���܂��B
	 * @returns �ǂݏo���ꂽ���l
	 */
	double num(const double & default_value = 0.0, std::string * error_message = nullptr) const;

	/** ���̗v�f�𕶎���Ƃ��ēǂݏo���܂��B
	 * @param default_str �ǂݍ��݂Ɏ��s�����ꍇ�ɂ͂��̕����񂪂��̂܂ܖ߂���܂��B
	 * @returns �ǂݏo���ꂽ������
	 */
	std::string str(const std::string & default_str = "", std::string * error_message = nullptr) const;


	/** ���̗v�f���t���O�l�Ƃ��ēǂݏo���܂��B
	 * @param default_flag �ǂݍ��݂Ɏ��s�����ꍇ�ɂ͂��̃t���O�l�����̂܂ܖ߂���܂��B
	 * @returns �ǂݏo���ꂽ�t���O
	 */
	bool is(const bool default_flag = false, std::string * error_message = nullptr) const;

	/** ���̗v�f���z��ł���ꍇ�A���̃T�C�Y��Ԃ��܂��B�X�J���v�f�Ɏg�p�����ꍇ�͎��s�t���O�������A0���Ԃ���܂��B���̎��s�t���O��failed�֐��ŎQ�Ƃł��܂��B
	 * @return �z��̃T�C�Y
	 */
	std::size_t size(std::string * error_message = nullptr) const;

	/** ���l��ݒ肵�܂��B
	 * ���݂���L�[���w�肳�ꂽ�ꍇ�́A���̗v�f�֏㏑���ۑ�����A�L�[�����݂��Ȃ��ꍇ�͐V�����쐬����܂��B�����K�w�ɂ킽��V�K�L�[�ݒ�ł����������삵�܂��B
	 * @param value �V�����ݒ肷�鐔�l
	 */
	void set(const double & value);
	void set(const std::string & str);
	void set(const bool flag);


	///////////////////////
	// Error Accessor
	///////////////////////

	/** [REMOVED]Get the data whether some error has occured or not.
	 * @returns true means some error has occured.
	 * @deprecated
	 */
	//bool isError(void) const;

	/** [REMOVED]Get the error dump.
	 * @returns the error dump text.
	 * @deprecated
	 */
	//std::string getError(void) const;

	/** ���O�̓���Ɏ��s���Ă��邩���擾���܂��B�܂��A�C�ӂł��̃G���[�Ɋւ��郁�b�Z�[�W���擾���邱�Ƃ��ł��܂��B
	 * ����:���̊֐��͒��O�̓���ɑ΂��錋�ʂ������܂��B���s�����N�G���������Ă��A���̃N�G�������������ꍇ�A���̌��false�i���s���Ă��Ȃ��j���Ԃ���܂��B
	 * @param message �G���[���b�Z�[�W���擾�������ꍇ�̂݁A������|�C���^��^���Ă�������
	 * @returns ���O�̓���Ɏ��s�����Ȃ�true
	 */
	bool failed(std::string * message = nullptr) const;

private:
	Json();
	Json(const picojson::value & v, const std::string & err_str);
	Json(const Json & copy);

	template<typename T> T get(const T & default_val, std::string * error_message) const;


	////////////////////////
	// Member Variable
	////////////////////////
	std::string err_str_;

	picojson::value json_value;
	

};

};

#endif