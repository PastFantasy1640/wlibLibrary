//////////////////////////////////////////////////////
// Logger.hpp
//
// MIT LICENSE
//////////////////////////////////////////////////////

#pragma once
#ifndef WLIB_LOGGER_HPP_
#define WLIB_LOGGER_HPP_

#include <string>

namespace wlib{

/**
 * ���ɊȒP�ȃ��O�N���X�ł��B���ꂼ��̃C���X�^���X�Ƀ^�O�t�����ł��A�܂��W���o�́A�t�@�C���o�̗͂L�����A���������ł��܂��B
 * �������Ɋւ��ẮAchangeLogLevel�֐��ɂă��O���x���̕ύX����ԍŏ��ɓK�X�؂�ւ��ĉ������B���O���x����kAll, kWarningAndError, kErrorOnly, kNoLogging�̂S���x���ŁA���ꂼ�ꂷ�ׂďo�́A�x���y�уG���[�A�G���[�̂݁A�����o�͂��Ȃ��A�ƂȂ��Ă��܂��B���̎��̌x���iWarning�j�́u���s�\�ȃG���[�v�ŁA�G���[�iError�j�́u���s�s�\�ȃG���[�v�̋敪�����Ƃ��Ă��܂��B���O���x���̓v���O�����ɂ����ċ��ʂł��B
 * �g�����́A�܂��R���X�g���N�^���Ăяo���A�����ɂă^�O���w�肵�܂��B�܂��󋵂ɉ����āA�W���o�́A�t�@�C���o�̗͂L���A������؂�ւ��ĉ������B
 * �����Ă��̌�́A���O���o�͂������^�C�~���O�ŁAinformation, warning, error�֐����g�p���܂��B
 * ��ԊȒP�Ȏg������`Logger("Hogehoge").information("foobar");`�Ƃ��邱�Ƃł��B�K���������ׂĂ̏ꍇ�ɂ����Ă��̕��@���œK�Ƃ͌���܂���B
 * �܂��A���ׂĂ̊֐��A�@�\�́A�X���b�h�Z�[�t���ۏ؂���Ă��܂��B
 * @version 1.2
 * @since 2017.10
 * @author S.Shirao
 */
class Logger {
public:

	/** ���O���x���萔
	 * ���O���x����kAll, kWarningAndError, kErrorOnly, kNoLogging��4���x��������܂��B
	 * kAll : ���ׂďo��
	 * kWarningAndError : �x���y�уG���[
	 * kError : �G���[�̂�
	 * kNoLogging : �����o�͂��Ȃ�
	 * �������A�x���iWarning�j�́u���s�\�ȃG���[�v�ŁA�G���[�iError�j�́u���s�s�\�ȃG���[�v�ƈӖ��t������Ă��܂��B
	 * �S�̂̃��O���x����changeLogLevel�֐��ɂĕύX���邱�Ƃ��ł��܂��B
	 * @see wlib::Logger::changeLogLevel
	 */
	enum LogLevel {
		kAll = 0,
		kWarningAndError = 1,
		kErrorOnly = 2,
		kNoLogging = 3
	};

	/** �^�O����
	 */
	const std::string tag_;

	/** �W���o�͂֏o�͂��邩�ǂ���
	 */
	const bool is_output_stdio_;
	
	/** �t�@�C���֏o�͂��邩�ǂ���
	 */
	const bool is_output_file_;

	/** ���O�t�@�C�����̎擾
	 */
	const std::string kLogFilename = "log.txt";

	/** �R���X�g���N�^
	 * �R���X�g���N�^���R�[������^�C�~���O�̎w��͂���܂���B�C���X�^���X��ێ�����K�v������܂���B
	 * @param tag �^�O�B��{�I�ɂ̓N���X�����w�肵�ĉ������B
	 * @param is_output_stdio �W���o�͂֏o�͂��邩�ǂ����B�f�t�H���g�ł�true���w�肳��Ă��܂��B
	 * @param is_output_file �t�@�C���֏o�͂��邩�ǂ����B�f�t�H���g�ł�true���w�肳��Ă��܂��B�t�@�C�����̎擾��getLogFilename�֐��ŉ\�ł��B
	 * @see wlib::Logger::getLogFilename
	 */
	explicit Logger(const std::string & tag, bool is_output_stdio = true, bool is_output_file = true);

	/** �f�X�g���N�^
	 */
	virtual ~Logger();

	/** �u���v�Ƃ��ďo��
	 * �w�肳�ꂽ��������A�u���v�Ƃ��ă��O�o�͂��܂��B
	 * @param text ���O������
	 */
	void information(const std::string & text);

	/** �u�x���v�Ƃ��ďo��
	 * �w�肳�ꂽ��������A�u�x���v�Ƃ��ă��O�o�͂��܂��B
	 * @param text ���O������
	 */
	void warning(const std::string & text);

	/** �u�G���[�v�Ƃ��ďo��
	 * �w�肳�ꂽ��������A�u�G���[�v�Ƃ��ă��O�o�͂��܂��B
	 * @param text ���O������
	 */
	void error(const std::string & text);
	
	/** ���O���x���̕ύX
	 * ���O���x���̓v���W�F�N�g�ɂċ��L����Ă��܂��B���O���x���̕ύX��ɁA�V���ɏo�͂���郍�O�ɑ΂��āA���̃��O���x���͓K�p����܂��B
	 * @param log_level �V�����w�肷�郍�O���x��
	 */
	void changeLogLevel(LogLevel log_level);


private:
	
	/** ���O���x���i�[�p�̕ϐ�
	 */
	static LogLevel log_level_;

	/** �f�t�H���g�R���X�g���N�^
	 * �f�t�H���g�R���X�g���N�^�͋֎~����Ă��܂��B����ɔ����A�R�s�[�R���X�g���N�^���p�ӂ���Ă��܂���B
	 */
	Logger() = delete;

	/** �o�͊֐�
	 * @param status �X�e�[�^�X������B�uINFO�v��uWARN�v�A�uERRO�v���i�[����܂��B
	 */
	void _write(const std::string & status, const std::string & text, const bool is_cerr = false);
};

};

#endif // wlib_LOGGER_HPP_
