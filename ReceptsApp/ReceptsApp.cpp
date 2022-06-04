#include <iostream>
#include <vector>
#include <string>
#include <map>

template<typename T, size_t n>
inline size_t arraySize(const T(&arr)[n])
{
	return n;
}

const std::string nameOfAllIngredientsInGramms[5] = { "Пшеничная мука", "Соль", "Сахар", "Moloko", "Масло" };
const std::string nameOfAllIngredientsInNumber[5] = { "Куриное яйцо", "Яблоко", "Морковь", "Баклажан", "Клубника" };
//std::multimap<std::string, std::string> category;
//std::string* categoryArray = {"Молочные"}

//
//class User
//{
//private:
//
//public:
//
//};
//
//class App //нормально ли что приложение одно, но так как это класс, то можно создать несколько объектов 
//{
//
//};
//
//class Dish
//{
//
//};

/*
	struct AmountCOnverter
	getAmountInGramms(Ingredients, int count )

	getAmountInNumber(int totalWeight, Ingr)
		return total / ingr.getWeigth()
	*/


class Ingredient
{
private:
	std::string _name;
	std::string _category;
public:
	void setIngredient(std::string name)
	{
		//std::multimap<std::string, std::string>::iterator it1;
		for (size_t i = 0; i < sizeof(nameOfAllIngredientsInGramms)/sizeof(nameOfAllIngredientsInGramms[0]); i++)
		{
			if (name == nameOfAllIngredientsInGramms[i])
			{
				_name = name;
				/*for (auto it = category.begin(); it != category.end(); it++)
				{
					if (it->second == name)
					{
						it1 = it;
						break;
					}
						
				}*/
			}
		}

		for (size_t i = 0; i < sizeof(nameOfAllIngredientsInNumber)/sizeof(nameOfAllIngredientsInNumber[0]); i++)
		{
			if (name == nameOfAllIngredientsInNumber[i])
			{
				_name = name;
				/*for (auto it = category.begin(); it != category.end(); it++)
				{
					if (it->second == name)
					{
						it1 = it;
						break;
					}

				}*/
			}
		}

		//_category = it1->first;
	}

	void ingredientOut()
	{
		std::cout << std::endl << _name << std::endl << _category << std::endl;
	}
};


class IngredientWithAmountInGramms : public Ingredient
{
private:
	int _amountGramms;
public:

	int getAmount()
	{
		return _amountGramms;
	}

	void setAmount(int amountGramms)
	{
		_amountGramms = amountGramms;
	}
};

class IngredientWithAmountInNumber : public Ingredient
{
private:
	int _amountNumber;
public:

	int getAmount()
	{
		return _amountNumber;
	}

	void setAmount(int amountNumber)
	{
		_amountNumber = amountNumber;
	}
};


class Recipe
{
private:
	std::vector<IngredientWithAmountInGramms> _ingredientsInGramms;
	std::vector<IngredientWithAmountInNumber> _ingredientsInNumber;
	unsigned int _numberOfSteps;   //число шагов приготовления блюда
	std::vector<std::string> _steps; //описание шагов приготовления блюда
public:
	//Recipe() : _numberOfSteps(0) {}
	

	void setNumberOfSteps(unsigned int numberOfSteps)
	{
		_numberOfSteps = numberOfSteps;
	}

	void setSteps(std::vector<std::string> steps)
	{
		std::string step;
		if (steps.size() != _numberOfSteps)
		{
			std::cout << "Ошибка: описаны не все шаги приготовления или описано больше шагов, чем требуется" << std::endl;
		}
		if (_numberOfSteps == 0)
		{
			std::cout << "Ошибка: число шагов приготовления блюда не задано" << std::endl;
		}
		else
		{
			_steps = steps;
		}
	}

	void addIngredient(std::string nameOfIngredient)
	{
		bool error = false;
		IngredientWithAmountInGramms ingredientGr;
		IngredientWithAmountInNumber ingredientNum;
	/*	while (stillNeedIngredient)
		{
			std::cout << "Назовите ингредиент, необходимый для приготовления блюда: ";
			std::cin >> nameOfIngredient;*/
			for (size_t i = 0; i < sizeof(nameOfAllIngredientsInGramms) / sizeof(nameOfAllIngredientsInGramms[0]); i++)
			{
				if (nameOfIngredient == nameOfAllIngredientsInGramms[i]) // поиск введеного ингредиента в константном массиве,
				{														 // состоящем из всех доступных приложению ингредиентов определенных в граммах
					ingredientGr.setIngredient(nameOfIngredient);
					_ingredientsInGramms.push_back(ingredientGr);
					error = false;
					return;
				}
				else if (nameOfIngredient == nameOfAllIngredientsInNumber[i]) // тут то же самое, но ингр.-ты определены в "штуках"
				{
					ingredientNum.setIngredient(nameOfIngredient);
					_ingredientsInNumber.push_back(ingredientNum);
					error = false;
					return;
				}
				error = true;  // "мнимый" error. Становится "настоящим" только, если это присваивание выполняется на последней итерации цикла
			}

			if (error == true)
			{
				std::cout << "Ошибка: bad input" << std::endl;
			}

			/*error = false;
			do 
			{
				char yesOrNo;
				std::cout << "Хотите ли назвать еще ингредиент? (Y/N): ";
				std::cin >> yesOrNo;
				switch (yesOrNo)
				{
				case('Y'):
					break;
				case('y'):
					break;
				case('N'):
					stillNeedIngredient = false;
					break;
				case('n'):
					stillNeedIngredient = false;
					break;
				default:
					error = true;
					std::cout << "Ошибка: bad input";
					break;
				}
			} while (error);*/
		//}
	}

	void recipeOut()
	{
		//size_t sizeOfSteps = sizeof(_steps) / sizeof(_steps[0]);  //либо надо проверить пустой ли steps?
		if ((_ingredientsInGramms.empty() && _ingredientsInNumber.empty()) || _steps.empty())
		{
			std::cout << "Ошибка: у рецепта не заданы ингредиенты или шаги приготовления" << std::endl;
		}
		else
		{
			std::cout << "Используемые ингредиетнты: ";
			for (size_t i = 0; i < _ingredientsInGramms.size(); i++)
			{
				_ingredientsInGramms[i].ingredientOut();
			}
			for (size_t i = 0; i < _ingredientsInNumber.size(); i++)
			{
				_ingredientsInNumber[i].ingredientOut();
			}
			std::cout << "Шаги приготовления: " << std::endl;
			for (size_t i = 0; i < _steps.size(); i++)
			{
				std::cout << i+1 << ". " << _steps[i] << std::endl;
			}
		}
	}
};

int main()
{
	setlocale(LC_ALL, "ru");
	Recipe Tort;
	Tort.setNumberOfSteps(1);
	Tort.setSteps({ "asdasd" });
	Tort.addIngredient("Moloko");
	Tort.recipeOut();
	//muka.setNumberOfSteps(4);
	//muka.setSteps();
	return 0;
}

//хочу, чтобы где-то была куча ингредиентов и в рецпте мы могли бы выбрать, какие из них есть используются в приготовлении блюда
//узнать про cout в методах класса