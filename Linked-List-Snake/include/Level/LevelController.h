#pragma once
#include "../../include/Level/LevelModel.h"
#include "../../include/Level/LevelView.h"

namespace Level {

	class LevelController {

	private:
		LevelModel* level_model;
		LevelView* level_view;

		void destroy();

	public:
		LevelController();
		~LevelController();

		void initialize();
		void update();
		void render();

		float getCellWidth();
		float getCellHeight();
	};

}