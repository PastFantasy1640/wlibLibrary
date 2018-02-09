#pragma comment(user, "jubeon professional header")
//////////////////////////////////////////////////////
// Scene.hpp
//
//////////////////////////////////////////////////////

#pragma once

#ifndef JUBEON_SCENE_HPP_
#define JUBEON_SCENE_HPP_

#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include "Graphics/LayerManager.hpp"

namespace jubeon {



/**
 * Sceneクラスは、ゲームの進行上の区切りとして活用されるクラス。ゲームの中心進行処理はこのクラスのメンバ関数として実行される。
 * Sceneクラスの使い方は2種類で、主な使い方としてはそれぞれのシーンを作ること、そして静的にシーンを管理し進行することである。
 * まず、Sceneクラスはインターフェースになっているため、これをpublic継承したクラスを作る必要があります。そのクラスにおいて、update関数は必ずオーバーライド実装しなければなりません。
 * そして、main関数などで、ゲーム起動準備が整った後にrun関数を実行します。run関数では、画面を立ち上げた後、毎フレームの画面描写とシステムのアップデートを交互に行います。
 * ブロッキング関数ではありますが、スレッド起動をしないため、main関数やそれに準ずる関数にて、threadを起動することをおすすめします。
 * 画面の破棄や、リソースの解除など、すべてのゲーム内機能を終了した後、この関数は終了します。
 * @sinse 2017/10
 * @version 2018/01
 * @author S.Shirao
 */
class Scene {
public:
typedef std::unique_ptr<Scene> Scene_UPtr;

	/** シーン名
	 */
	const std::string scene_name_;

	/** コンストラクタ
	 * シーン名を登録する必要があります。
	 * @param name シーン名
	 */
	Scene(const std::string & name);

	/** デストラクタ
	 */
	virtual ~Scene();

	/** 
	 * 実行関数。ブロッキング関数です。ウィンドウの生成、実行から、ウィンドウ終了まで行い、関数を終了します。
	 * @param layer_manager レイヤーマネージャーのshared_ptr
	 * @param first_scene 最初のシーンのunique_ptr
	 */
	static void run(const LayerManager_SPtr & main_window, Scene_UPtr && first_scene);

	/**
	 * 終了の割り込みをします。スレッドセーフです。
	 */
	static void interrupt(void);

protected:

	/** 
	 * 次のシーンを設定し、シーン遷移を行います。
	 * @param next_scene 次のシーンのunique_ptr
	 */
	void setNextScene(Scene_UPtr && next_scene);

	/**
	 * Sceneの処理関数。この関数のブロッキングにより、全体の処理が止まってしまうため、できるだけ迅速な処理を行うようにし、ループ処理は書かないでください。
	 * @return 0ならシーン続行、0以外ならゲームを終了します。正の数字が正常終了、負の数字が異常終了と意味合いを持たせてください。
	 */
	virtual int update(void) = 0;
	
	/**
	 * ウィンドウを取得します。絶対にdeleteしてはいけません。
	 * @return ウィンドウのポインター
	 */
	jubeon::LayerManager * getLayerManager();

private:
	Scene() = delete;

	/** 次のシーン
	 */
	static Scene_UPtr next_scene_;
	
	/** 現在のシーン
	 */
	static Scene_UPtr current_scene_;
	

	static std::mutex mutex_;

	/** 終了割り込みフラグ
	 */
	static bool interrupted_;
	
	/** レイヤーマネージャのポインタ
	 */
	static LayerManager_SPtr layer_manager_;

	/**
	 * 終了割り込みがあったか
	 * @return trueなら割り込みあり
	 */
	static bool _isInterrupted(void);
};

};

#endif //JUBEON_SCENE_HPP_

