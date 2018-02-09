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
 * Jsonファイルの入出力クラスです。外部ライブラリpicojsonに依存していて、picojsonのラッパークラスとなっています。
 * 使い方は非常にシンプルです。phpの仮想配列のようになってますので、キーワードを根から順に指定してあげるだけで読み込みができます。
 * @version 0.2(書き込み未実装)
 * @author S.Shirao
 */
class Json {
public:

	/** コンストラクタ
	 * コンストラクタでjsonテキストを受け付け、デコードを行います。デコードに失敗した場合、jsonインスタンスは生成されますがいかなる読み込みにも失敗します。また、failed関数を使うことで、読み込みに失敗したかどうかわかります。
	 * Jsonクラスでは、例えばファイルからの読み込み関数などは実装していません。必ずしもファイルから読み込むのがすべてではないからです。
	 * @param json_str jsonテキスト
	 */
	explicit Json(const std::string & json_str);

	/** デストラクタ
	 * 今のところNOPです。
	 */
	virtual ~Json();

	/** 子要素へアクセスします。
	 * @param key キー文字列
	 * @returns wlib::Json 子をルートとしたJsonツリー
	 */
	Json operator[](const std::string & key);

	/** Access the json array in index
	 * @param index the index of the json array.
	 * @returns wlib::Json Instance
	 */
	Json operator[](const std::size_t & index);

	/** その要素を数値として読み出します。
	 * @param default_value 読み込みに失敗した場合にはこの数値がそのまま戻されます。
	 * @returns 読み出された数値
	 */
	double num(const double & default_value = 0.0);

	/** その要素を文字列として読み出します。
	 * @param default_str 読み込みに失敗した場合にはこの文字列がそのまま戻されます。
	 * @returns 読み出された文字列
	 */
	std::string str(const std::string & default_str = "");


	/** その要素をフラグ値として読み出します。
	 * @param default_flag 読み込みに失敗した場合にはこのフラグ値がそのまま戻されます。
	 * @returns 読み出されたフラグ
	 */
	bool is(const bool default_flag = false);

	/** その要素が配列である場合、そのサイズを返します。スカラ要素に使用した場合は失敗フラグが立ち、0が返されます。この失敗フラグはfailed関数で参照できます。
	 * @return 配列のサイズ
	 */
	std::size_t size(void);

	/** 数値を設定します。
	 * 存在するキーが指定された場合は、その要素へ上書き保存され、キーが存在しない場合は新しく作成されます。複数階層にわたる新規キー設定でも正しく動作します。
	 * @param value 新しく設定する数値
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

	/** 直前の動作に失敗しているかを取得します。また、任意でそのエラーに関するメッセージを取得することもできます。
	 * 注意:この関数は直前の動作に対する結果を示します。失敗したクエリがあっても、次のクエリが成功した場合、その後はfalse（失敗していない）が返されます。
	 * @param message エラーメッセージを取得したい場合のみ、文字列ポインタを与えてください
	 * @returns 直前の動作に失敗したならtrue
	 */
	bool failed(std::string * message = nullptr);

private:
	Json();
	Json(const picojson::value & v, const std::shared_ptr<std::string> & shp_err_str, const std::shared_ptr<bool> & shp_first_flag);
	Json(const Json & copy);

	template<typename T> T get(const T & default_val);


	////////////////////////
	// Member Variable
	////////////////////////
	std::shared_ptr<std::string> shp_err_str;
	std::shared_ptr<bool> shp_first_flag;

	picojson::value json_value;

};

};

//INLINE FUNCTIONS
inline bool wlib::Json::isError(void) const{
	if (this->shp_err_str) {
		return !this->shp_err_str->empty();
	}
	return false;
}

#endif