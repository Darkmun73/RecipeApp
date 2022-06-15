#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Container.h"

template<typename T, size_t n>
inline size_t arraySize(const T(&arr)[n])
{
	return n;
}

class Category;
class Ingredient;
MyBidirectionalList<Category> allCategories;

class User
{
private:
	std::string _nickname = "Guest";
	unsigned int id = NULL;

public:
	User(std::string nickname) : _nickname(nickname)
	{
		srand(time(0));
		id = rand(); //понимаю, что так не правильно делать
	}
};
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
class Category
{
private:
	std::string _name;
	std::vector<Ingredient> _ingredients;
public:
	Category() : _name("nonameCategory"), _ingredients(std::vector<Ingredient>()) { }
	Category(std::string name) : _name(name), _ingredients(std::vector<Ingredient>()) { }
	Category(std::string name, std::vector<Ingredient> ingredients) : _name(name), _ingredients(ingredients) { }
	~Category() {}

	void setName(std::string name)
	{
		_name = name;
	}

	std::string getName()
	{
		return _name;
	}

	std::vector<Ingredient>& getIngredients() //надеюсь то, что я сделал геттер с ссылкой, это норма
	{
		return _ingredients;
	}
};

class Ingredient
{
private:
	std::string _name;
	std::string _category = "nonameCategory";
	int _amount = NULL;

public:
	Ingredient(std::string name, std::string category) : _name(name), _category(category) {}

	Ingredient(std::string name = "nonameIngredient")
	{
		MyBidirectionalList<Category>::iterator iter;

		//Среди всех категорий из allCategories ищу ту, в которой есть название name ингредиента.
		iter = std::find_if(allCategories.begin(), allCategories.end(),
			[name](Category categ)
			{
				return std::find_if(categ.getIngredients().begin(), categ.getIngredients().end(), //здесь ищем ингредиент с названием name
					[name](Ingredient ingr) 
					{ 
						return ingr.getName() == name;
					}
				) != categ.getIngredients().end(); //если найден, то true, в противном случае false
			}
		); //здесь find_if в find_if'е, если так можно выразиться)) прошу прощения, если сложно прочитать
		
		//Если такая категория есть, то...
		if (iter != allCategories.end())
		{
			_name = name;
			_category = iter->getName();
		}
		else //если - нет, то...
		{
			_name = "nonameIngredient";
		}
	}

	void ingredientOut()
	{
		std::cout << std::endl << _name << std::endl << _category << std::endl;
	}

	std::string getName()
	{
		return _name;
	}

	Category getCategory()
	{
		return _category;
	}

	int getAmount()
	{
		return _amount;
	}

	void setAmount(int amount)
	{
		_amount = amount;
	}
};

class Recipe
{
private:
	std::vector<Ingredient> _ingredients;
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

	//void addIngredient(std::string nameOfIngredient)
	//{
	//	bool error = false;
	//	IngredientWithAmountInGramms ingredientGr;
	//	IngredientWithAmountInNumber ingredientNum;
	///*	while (stillNeedIngredient)
	//	{
	//		std::cout << "Назовите ингредиент, необходимый для приготовления блюда: ";
	//		std::cin >> nameOfIngredient;*/
	//		for (size_t i = 0; i < sizeof(nameOfAllIngredientsInGramms) / sizeof(nameOfAllIngredientsInGramms[0]); i++)
	//		{
	//			if (nameOfIngredient == nameOfAllIngredientsInGramms[i]) // поиск введеного ингредиента в константном массиве,
	//			{														 // состоящем из всех доступных приложению ингредиентов определенных в граммах
	//				ingredientGr.setIngredient(nameOfIngredient);
	//				_ingredientsInGramms.push_back(ingredientGr);
	//				error = false;
	//				return;
	//			}
	//			else if (nameOfIngredient == nameOfAllIngredientsInNumber[i]) // тут то же самое, но ингр.-ты определены в "штуках"
	//			{
	//				ingredientNum.setIngredient(nameOfIngredient);
	//				_ingredientsInNumber.push_back(ingredientNum);
	//				error = false;
	//				return;
	//			}
	//			error = true;  // "мнимый" error. Становится "настоящим" только, если это присваивание выполняется на последней итерации цикла
	//		}

	//		if (error == true)
	//		{
	//			std::cout << "Ошибка: bad input" << std::endl;
	//		}

	//		/*error = false;
	//		do 
	//		{
	//			char yesOrNo;
	//			std::cout << "Хотите ли назвать еще ингредиент? (Y/N): ";
	//			std::cin >> yesOrNo;
	//			switch (yesOrNo)
	//			{
	//			case('Y'):
	//				break;
	//			case('y'):
	//				break;
	//			case('N'):
	//				stillNeedIngredient = false;
	//				break;
	//			case('n'):
	//				stillNeedIngredient = false;
	//				break;
	//			default:
	//				error = true;
	//				std::cout << "Ошибка: bad input";
	//				break;
	//			}
	//		} while (error);*/
	//	//}
	//}

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

void split(std::string str, std::vector<std::string>& data)
{
	while (!str.empty())
	{
		auto word_end = str.find("  ");
		if (word_end == -1)
		{
			data.push_back(str);
			str.clear();
		}
		else
		{
			data.push_back(str.substr(0, word_end));
			str.erase(0, word_end + 2);
		}
	}
}

//Заполнение контейнера со всеми категориями ингредиентов (и самими ингредиентами внутри каждой категории)
void fillAllCategories()
{
	std::ifstream CategoriesIn("Categories.txt");
	if (CategoriesIn.fail())
	{
		std::cerr << "Ошибка открытия файла";
		exit(1);
	}

	std::string temp;
	std::vector<std::string> ingr;
	allCategories.push_back(Category());
	MyBidirectionalList<Category>::iterator iter = allCategories.begin();

	while (!CategoriesIn.eof())
	{

		std::getline(CategoriesIn, temp);
		split(temp, ingr);
		iter->setName(ingr[0]);
		for (auto& i : ingr)
		{
			if (i != ingr[0])
			{
				iter->getIngredients().push_back(Ingredient(i, ingr[0]));
			}
		}
		allCategories.push_back(Category());
		iter++;
		ingr.clear();
	}
	allCategories.pop_back();
}

int main()
{
	setlocale(LC_ALL, "ru");
	fillAllCategories();
	for (auto iter = allCategories.begin(); iter != allCategories.end(); iter++)
	{
		std::cout << iter->getName() << " ";
		for (auto iter1 = iter->getIngredients().begin(); iter1 != iter->getIngredients().end(); iter1++)
		{
			std::cout << iter1->getName() << " ";
		}
		std::cout << std::endl;
	}
	/*auto a = 5;
	Recipe Tort;
	Tort.setNumberOfSteps(1);
	Tort.setSteps({ "asdasd" });
	Tort.addIngredient("Moloko");
	Tort.recipeOut();*/
	//muka.setNumberOfSteps(4);
	//muka.setSteps();
	return 0;
}

//хочу, чтобы где-то была куча ингредиентов и в рецпте мы могли бы выбрать, какие из них есть используются в приготовлении блюда