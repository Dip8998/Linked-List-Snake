#include "UI/LinkedListUI/LinkedListSelectionUIController.h"
#include "Main/GameService.h"
#include "Graphics/GraphicService.h"
#include "Sound/SoundService.h"
#include "Event/EventService.h"
#include "UI/UIElement/ButtonView.h"
#include "UI/UIElement/ImageView.h"
#include "Global/Config.h"
#include "Level/LevelService.h"

namespace UI
{
    using namespace UIElement;
    using namespace Global;
    using namespace Event;
    using namespace Sound;
    using namespace Main;
    using namespace LinkedListUI;

    namespace LinkedListUI
    {
        LinkedListSelectionUIController::LinkedListSelectionUIController()
        {
            createButtons();
            createImage();
        }

        LinkedListSelectionUIController::~LinkedListSelectionUIController()
        {
            destroy();
        }

        void LinkedListSelectionUIController::initialize()
        {
            initializeBackgroundImage();
            initializeButtons();
            registerButtonCallback();
        }

        void LinkedListSelectionUIController::createImage()
        {
            background_image = new ImageView();
        }

        void LinkedListSelectionUIController::createButtons()
        {
            level_one_button = new ButtonView();
            level_two_button = new ButtonView();
            menu_button = new ButtonView();
        }

        void LinkedListSelectionUIController::initializeBackgroundImage()
        {
            sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();

            background_image->initialize(Config::background_texture_path, game_window->getSize().x, game_window->getSize().y, sf::Vector2f(0, 0));
            background_image->setImageAlpha(background_alpha);
        }

        void LinkedListSelectionUIController::initializeButtons()
        {
            float x_position = calculateLeftOffsetForButton();

            level_one_button->initialize("Level One Button", Config::level_one_button_texture_path, button_width, button_height, sf::Vector2f(x_position, level_one_button_y_position));
            level_two_button->initialize("Level Two Button", Config::level_two_button_texture_path, button_width, button_height, sf::Vector2f(x_position, level_two_button_y_position));
            menu_button->initialize("Menu Button", Config::menu_button_texture_path, button_width, button_height, sf::Vector2f(x_position, menu_button_y_position));
        }

        void LinkedListSelectionUIController::registerButtonCallback()
        {
            level_one_button->registerCallbackFuntion(std::bind(&LinkedListSelectionUIController::singleLinkedButtonCallback, this));
            level_two_button->registerCallbackFuntion(std::bind(&LinkedListSelectionUIController::doubleLinkedButtonCallback, this));
            menu_button->registerCallbackFuntion(std::bind(&LinkedListSelectionUIController::menuButtonCallback, this));
        }

        float LinkedListSelectionUIController::calculateLeftOffsetForButton()
        {
            sf::RenderWindow* game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
            return (static_cast<float>(game_window->getSize().x) / 2) - button_width / 2;
        }

        void LinkedListSelectionUIController::singleLinkedButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            GameService::setGameState(GameState::GAMEPLAY);
            //ServiceLocator::getInstance()->getLevelService()->setCurrentLevelNumber(Level::LevelNumber::ONE);
            //ServiceLocator::getInstance()->getLevelService()->createLevel(Level::LevelNumber::ONE);
        }

        void LinkedListSelectionUIController::doubleLinkedButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            GameService::setGameState(GameState::GAMEPLAY);
            //ServiceLocator::getInstance()->getLevelService()->setCurrentLevelNumber(Level::LevelNumber::TWO);
            //ServiceLocator::getInstance()->getLevelService()->createLevel(Level::LevelNumber::TWO);
        }

        void LinkedListSelectionUIController::menuButtonCallback()
        {
            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            GameService::setGameState(GameState::MAIN_MENU);
        }

        void LinkedListSelectionUIController::update()
        {
            background_image->update();
            level_one_button->update();
            level_two_button->update();
            menu_button->update();
        }

        void LinkedListSelectionUIController::render()
        {
            background_image->render();
            level_one_button->render();
            level_two_button->render();
            menu_button->render();
        }

        void LinkedListSelectionUIController::show()
        {
            background_image->show();
            level_one_button->show();
            level_two_button->show();
            menu_button->show();
        }

        void LinkedListSelectionUIController::destroy()
        {
            delete (background_image);
            delete (level_one_button);
            delete (level_two_button);
            delete (menu_button);
        }
    }
}