#pragma once

namespace Player {

	class SnakeController {
	public:
		SnakeController();
		~SnakeController();

		void initialize();
		void update();
		void render();
	};

}