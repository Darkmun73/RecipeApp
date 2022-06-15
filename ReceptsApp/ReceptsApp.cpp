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


MyBidirectionalList<Category>::iterator& findNameOfIngredient(std::string);
class Ingredient
{
private:
	std::string _name;
	std::string _category = "nonameCategory";

public:
	Ingredient(std::string name, std::string category) : _name(name), _category(category) {}
	Ingredient(std::string name = "nonameIngredient")
	{
		MyBidirectionalList<Category>::iterator iter = findNameOfIngredient(name);
		
		//Если есть категория, в которой есть ингредиент с названием name, то...
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
		std::cout << _name << std::endl;
	}

	std::string getName()
	{
		return _name;
	}

	Category getCategory()
	{
		return _category;
	}
};

//Среди всех категорий из allCategories ищу ту, в которой есть название nameOfIngredient ингредиента.
MyBidirectionalList<Category>::iterator& findNameOfIngredient(std::string nameOfIngredient)
{
	MyBidirectionalList<Category>::iterator iter;

	iter = std::find_if(allCategories.begin(), allCategories.end(),
		[nameOfIngredient](Category categ)
		{
			return std::find_if(categ.getIngredients().begin(), categ.getIngredients().end(), //здесь ищем ингредиент с названием name
				[nameOfIngredient](Ingredient ingr)
				{
					return ingr.getName() == nameOfIngredient;
				}
			) != categ.getIngredients().end(); //если найден, то true, в противном случае false
		}
	);	//здесь find_if в find_if'е, если так можно выразиться)) прошу прощения, если сложно прочитать

	return iter;
}

class Recipe //названия блюда по которому написан рецепт должно быть в классе Dish, но я пока не успел его реализовать(
{
private:
	std::vector<Ingredient> _ingredients;
	unsigned int _numberOfSteps;   //число шагов в рецепте
	std::vector<std::string> _steps; //описание шагов в рецепте

public:
	Recipe() : _numberOfSteps(0) {}

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
		MyBidirectionalList<Category>::iterator iter = findNameOfIngredient(nameOfIngredient);
		if (iter != allCategories.end())
		{
			_ingredients.push_back(Ingredient(nameOfIngredient, iter->getName()));
		}
		else
		{
			std::cout << "Ошибка: такого ингредиента нет в базе" << std::endl;
		}
	}

	void recipeOut()
	{
		if (_ingredients.empty() || _steps.empty())
		{
			std::cout << "Ошибка: у рецепта не заданы ингредиенты или шаги приготовления" << std::endl;
		}
		else
		{
			std::cout << "Используемые ингредиетнты: " << std::endl;
			for (size_t i = 0; i < _ingredients.size(); i++)
			{
				_ingredients[i].ingredientOut();
			}
			std::cout << std::endl << "Шаги приготовления: " << std::endl;
			for (size_t i = 0; i < _steps.size(); i++)
			{
				std::cout << i+1 << ". " << _steps[i] << std::endl;
			}
			std::cout << "----------------" << std::endl;
		}
	}
};

//будущий класс блюда
class Dish
{

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

//Заполнение контейнера allCategories со всеми категориями ингредиентов (и самими ингредиентами внутри каждой категории)
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
	Recipe Tort;
	Tort.setNumberOfSteps(1);
	Tort.setSteps({ "asdasd" });
	Tort.addIngredient("Молоко");
	Tort.addIngredient("Говядина");
	Tort.addIngredient("Рисовая мука");
	Tort.recipeOut();

	Tort.addIngredient("Что-то");
	Tort.recipeOut();
	return 0;
}

//хочу, чтобы где-то была куча ингредиентов и в рецпте мы могли бы выбрать, какие из них есть используются в приготовлении блюда