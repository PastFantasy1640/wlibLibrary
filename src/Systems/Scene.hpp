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
 * Scene�N���X�́A�Q�[���̐i�s��̋�؂�Ƃ��Ċ��p�����N���X�B�Q�[���̒��S�i�s�����͂��̃N���X�̃����o�֐��Ƃ��Ď��s�����B
 * Scene�N���X�̎g������2��ނŁA��Ȏg�����Ƃ��Ă͂��ꂼ��̃V�[������邱�ƁA�����ĐÓI�ɃV�[�����Ǘ����i�s���邱�Ƃł���B
 * �܂��AScene�N���X�̓C���^�[�t�F�[�X�ɂȂ��Ă��邽�߁A�����public�p�������N���X�����K�v������܂��B���̃N���X�ɂ����āAupdate�֐��͕K���I�[�o�[���C�h�������Ȃ���΂Ȃ�܂���B
 * �����āAmain�֐��ȂǂŁA�Q�[���N�����������������run�֐������s���܂��Brun�֐��ł́A��ʂ𗧂��グ����A���t���[���̉�ʕ`�ʂƃV�X�e���̃A�b�v�f�[�g�����݂ɍs���܂��B
 * �u���b�L���O�֐��ł͂���܂����A�X���b�h�N�������Ȃ����߁Amain�֐��₻��ɏ�����֐��ɂāAthread���N�����邱�Ƃ��������߂��܂��B
 * ��ʂ̔j����A���\�[�X�̉����ȂǁA���ׂẴQ�[�����@�\���I��������A���̊֐��͏I�����܂��B
 * @sinse 2017/10
 * @version 2018/01
 * @author S.Shirao
 */
class Scene {
public:
typedef std::unique_ptr<Scene> Scene_UPtr;

	/** �V�[����
	 */
	const std::string scene_name_;

	/** �R���X�g���N�^
	 * �V�[������o�^����K�v������܂��B
	 * @param name �V�[����
	 */
	Scene(const std::string & name);

	/** �f�X�g���N�^
	 */
	virtual ~Scene();

	/** 
	 * ���s�֐��B�u���b�L���O�֐��ł��B�E�B���h�E�̐����A���s����A�E�B���h�E�I���܂ōs���A�֐����I�����܂��B
	 * @param layer_manager ���C���[�}�l�[�W���[��shared_ptr
	 * @param first_scene �ŏ��̃V�[����unique_ptr
	 */
	static void run(const LayerManager_SPtr & main_window, Scene_UPtr && first_scene);

	/**
	 * �I���̊��荞�݂����܂��B�X���b�h�Z�[�t�ł��B
	 */
	static void interrupt(void);

protected:

	/** 
	 * ���̃V�[����ݒ肵�A�V�[���J�ڂ��s���܂��B
	 * @param next_scene ���̃V�[����unique_ptr
	 */
	void setNextScene(Scene_UPtr && next_scene);

	/**
	 * Scene�̏����֐��B���̊֐��̃u���b�L���O�ɂ��A�S�̂̏������~�܂��Ă��܂����߁A�ł��邾���v���ȏ������s���悤�ɂ��A���[�v�����͏����Ȃ��ł��������B
	 * @return 0�Ȃ�V�[�����s�A0�ȊO�Ȃ�Q�[�����I�����܂��B���̐���������I���A���̐������ُ�I���ƈӖ��������������Ă��������B
	 */
	virtual int update(void) = 0;
	
	/**
	 * �E�B���h�E���擾���܂��B��΂�delete���Ă͂����܂���B
	 * @return �E�B���h�E�̃|�C���^�[
	 */
	jubeon::LayerManager * getLayerManager();

private:
	Scene() = delete;

	/** ���̃V�[��
	 */
	static Scene_UPtr next_scene_;
	
	/** ���݂̃V�[��
	 */
	static Scene_UPtr current_scene_;
	

	static std::mutex mutex_;

	/** �I�����荞�݃t���O
	 */
	static bool interrupted_;
	
	/** ���C���[�}�l�[�W���̃|�C���^
	 */
	static LayerManager_SPtr layer_manager_;

	/**
	 * �I�����荞�݂���������
	 * @return true�Ȃ犄�荞�݂���
	 */
	static bool _isInterrupted(void);
};

};

#endif //JUBEON_SCENE_HPP_

