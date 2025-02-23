#pragma once
#include <SFML/Graphics.hpp>
#include "UI/Interface/IUIController.h"
#include "UI/UIElement/ButtonView.h"
#include "UI/UIElement/ImageView.h"

namespace UI
{
	namespace LinkedListUI
	{
		class LinkedListSelectionUIController : public Interface::IUIController
		{
		private:
			// Constants:
			const float button_width = 400.f;
			const float button_height = 140.f;

			const float level_one_button_y_position = 500.f;
			const float level_two_button_y_position = 700.f;
			const float menu_button_y_position = 900.f;

			const float background_alpha = 85.f;

			UI::UIElement::ImageView* background_image;

			UI::UIElement::ButtonView* level_one_button;
			UI::UIElement::ButtonView* level_two_button;
			UI::UIElement::ButtonView* menu_button;

			void createImage();
			void createButtons();

			void initializeBackgroundImage();
			void initializeButtons();

			void registerButtonCallback();
			float calculateLeftOffsetForButton();

			void singleLinkedButtonCallback();
			void doubleLinkedButtonCallback();

			void menuButtonCallback();

			void destroy();

		public:
			LinkedListSelectionUIController();
			~LinkedListSelectionUIController();

			void initialize() override;
			void update() override;
			void render() override;
			void show() override;
		};
	}
}