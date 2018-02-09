#include "Scene.hpp"
#include "Logger.hpp"
#include "Debug/layer/FramerateLayer.hpp"

std::mutex jubeon::Scene::mutex_;
std::unique_ptr<jubeon::Scene> jubeon::Scene::next_scene_;
std::unique_ptr<jubeon::Scene> jubeon::Scene::current_scene_;
std::shared_ptr<jubeon::LayerManager> jubeon::Scene::layer_manager_;
bool jubeon::Scene::interrupted_ = false;

jubeon::Scene::Scene(const std::string & name)
 : scene_name_(name) {}

jubeon::Scene::~Scene(){
}

jubeon::LayerManager * jubeon::Scene::getLayerManager() {
	return this->layer_manager_.get();
}

void jubeon::Scene::run(const LayerManager_SPtr & layer_manager, Scene_UPtr && first_scene) {
	
	//Copy
	Scene::layer_manager_ = layer_manager;
	Scene::current_scene_ = std::move(first_scene);
	
	//Accessment Check
	if (!Scene::layer_manager_) { Logger("Scene").error("Main window was nullptr."); return; }
	if (!Scene::current_scene_) { Logger("Scene").error("First scene was empty."); return; }

	//Window Create
	if (!Scene::layer_manager_->createWindow()) { Logger("Scene").error("Failed to create window."); return; }
	
	//Logging
	Logger("Scene").information("Start " + Scene::current_scene_->scene_name_ + " scene main loop.");

	//Add System Layer
	std::shared_ptr<FramerateLayer> framerate_layer = std::make_shared<FramerateLayer>();
	framerate_layer->initLayer();
	Scene::layer_manager_->addLayer(framerate_layer, 0);
		
	//Main loop
	int ret = 0;
	while (ret == 0 && Scene::current_scene_ && !Scene::_isInterrupted()) {
		//updates
		ret = Scene::current_scene_->update();
		Scene::layer_manager_->drawAllLayers();

		if (Scene::next_scene_) {
			Scene::current_scene_ = std::move(Scene::next_scene_);
            Logger("Scene").information("Move to next " + Scene::current_scene_->scene_name_ +" scene.");
		}
	}

	//Close Game
    Logger("Scene").information("Closing the scene process.");
	Scene::layer_manager_->closeAllLayers();
	Scene::layer_manager_->closeWindow();
    Logger("Scene").information("Finished Closing.");
}

void jubeon::Scene::interrupt() {
	std::lock_guard<std::mutex> lock(Scene::mutex_);
	Scene::interrupted_ = true;
}

bool jubeon::Scene::_isInterrupted() {
	std::lock_guard<std::mutex> lock(Scene::mutex_);
	return Scene::interrupted_;
}

void jubeon::Scene::setNextScene(Scene_UPtr && next_scene){
	std::lock_guard<std::mutex> lock(this->mutex_);
	this->next_scene_ = std::move(next_scene);
}
