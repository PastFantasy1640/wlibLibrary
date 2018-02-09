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
 * 非常に簡単なログクラスです。それぞれのインスタンスにタグ付けができ、また標準出力、ファイル出力の有効化、無効化ができます。
 * 初期化に関しては、changeLogLevel関数にてログレベルの変更を一番最初に適宜切り替えて下さい。ログレベルはkAll, kWarningAndError, kErrorOnly, kNoLoggingの４レベルで、それぞれすべて出力、警告及びエラー、エラーのみ、何も出力しない、となっています。この時の警告（Warning）は「続行可能なエラー」で、エラー（Error）は「続行不可能なエラー」の区分分けとしています。ログレベルはプログラムにおいて共通です。
 * 使い方は、まずコンストラクタを呼び出し、引数にてタグを指定します。また状況に応じて、標準出力、ファイル出力の有効、無効を切り替えて下さい。
 * そしてその後は、ログを出力したいタイミングで、information, warning, error関数を使用します。
 * 一番簡単な使い方は`Logger("Hogehoge").information("foobar");`とすることです。必ずしもすべての場合においてこの方法が最適とは限りません。
 * また、すべての関数、機能は、スレッドセーフが保証されています。
 * @version 1.2
 * @since 2017.10
 * @author S.Shirao
 */
class Logger {
public:

	/** ログレベル定数
	 * ログレベルはkAll, kWarningAndError, kErrorOnly, kNoLoggingの4レベルがあります。
	 * kAll : すべて出力
	 * kWarningAndError : 警告及びエラー
	 * kError : エラーのみ
	 * kNoLogging : 何も出力しない
	 * ただし、警告（Warning）は「続行可能なエラー」で、エラー（Error）は「続行不可能なエラー」と意味付けされています。
	 * 全体のログレベルをchangeLogLevel関数にて変更することができます。
	 * @see wlib::Logger::changeLogLevel
	 */
	enum LogLevel {
		kAll = 0,
		kWarningAndError = 1,
		kErrorOnly = 2,
		kNoLogging = 3
	};

	/** タグ文字
	 */
	const std::string tag_;

	/** 標準出力へ出力するかどうか
	 */
	const bool is_output_stdio_;
	
	/** ファイルへ出力するかどうか
	 */
	const bool is_output_file_;

	/** ログファイル名の取得
	 */
	const std::string kLogFilename = "log.txt";

	/** コンストラクタ
	 * コンストラクタをコールするタイミングの指定はありません。インスタンスを保持する必要もありません。
	 * @param tag タグ。基本的にはクラス名を指定して下さい。
	 * @param is_output_stdio 標準出力へ出力するかどうか。デフォルトではtrueが指定されています。
	 * @param is_output_file ファイルへ出力するかどうか。デフォルトではtrueが指定されています。ファイル名の取得はgetLogFilename関数で可能です。
	 * @see wlib::Logger::getLogFilename
	 */
	explicit Logger(const std::string & tag, bool is_output_stdio = true, bool is_output_file = true);

	/** デストラクタ
	 */
	virtual ~Logger();

	/** 「情報」として出力
	 * 指定された文字列を、「情報」としてログ出力します。
	 * @param text ログ文字列
	 */
	void information(const std::string & text);

	/** 「警告」として出力
	 * 指定された文字列を、「警告」としてログ出力します。
	 * @param text ログ文字列
	 */
	void warning(const std::string & text);

	/** 「エラー」として出力
	 * 指定された文字列を、「エラー」としてログ出力します。
	 * @param text ログ文字列
	 */
	void error(const std::string & text);
	
	/** ログレベルの変更
	 * ログレベルはプロジェクトにて共有されています。ログレベルの変更後に、新たに出力されるログに対して、そのログレベルは適用されます。
	 * @param log_level 新しく指定するログレベル
	 */
	void changeLogLevel(LogLevel log_level);


private:
	
	/** ログレベル格納用の変数
	 */
	static LogLevel log_level_;

	/** デフォルトコンストラクタ
	 * デフォルトコンストラクタは禁止されています。これに伴い、コピーコンストラクタも用意されていません。
	 */
	Logger() = delete;

	/** 出力関数
	 * @param status ステータス文字列。「INFO」や「WARN」、「ERRO」が格納されます。
	 */
	void _write(const std::string & status, const std::string & text, const bool is_cerr = false);
};

};

#endif // wlib_LOGGER_HPP_
