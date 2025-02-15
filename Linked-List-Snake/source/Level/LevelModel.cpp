#include "Level/LevelModel.h"
#include "LevelController.h"

namespace Level
{
	LevelModel::LevelModel() = default;

	LevelModel::~LevelModel() = default;

	void LevelModel::initialize(int width, int height)
	{
		cell_width = width / number_of_columns;
		cell_height = height / number_of_rows;
	}

	float LevelModel::getCellWidth()
	{
		return cell_width;
	}

	float LevelModel::getCellHeight()
	{
		return cell_height;
	}

	void LevelModel::initializeLevelData()
	{
		level_configurations.push_back(LevelData(Level::LevelNumber::ONE, &level_one_element_list));
		level_configurations.push_back(LevelData(Level::LevelNumber::TWO, &level_two_element_list));
	}

	const std::vector<Element::ElementData>& LevelModel::getElementDataList(int level_to_load)
	{
		return *level_configurations[level_to_load].element_data_list;
	}
}