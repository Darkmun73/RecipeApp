#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Container.h"


class Category;
class Ingredient;
MyBidirectionalList<Category> allCategories;

class User
{
private:
	std::string _nickname;
	unsigned int _id;

public:
	User() : _nickname("guest"), _id(NULL) {}
	User(std::string nickname) : _nickname(nickname)
	{
		srand(time(0));
		_id = rand(); //понимаю, что так не правильно делать
	}
	std::string getNickname()
	{
		return _nickname;
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


class Dish
{
private:
	class Recipe //названия блюда по которому написан рецепт должно быть в классе Dish, но я пока не успел его реализовать(
	{
	private:
		User _user; //пользователь добавивший рецепт
		std::vector<Ingredient> _ingredients; //ингредиенты используемые в рецепте
		std::vector<std::string> _steps; //описание шагов в рецепте
		unsigned int _numberOfSteps;   //число шагов в рецепте

	public:
		Recipe() : _numberOfSteps(NULL) {}
		Recipe(const User& user, const unsigned int& numberOfSteps = 0, const std::vector<std::string>& steps = std::vector<std::string>(),
			const std::vector<Ingredient>& ingredients = std::vector<Ingredient>()) : _user(user), _numberOfSteps(numberOfSteps), _steps(steps), _ingredients(ingredients) {}

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

		User getUser()
		{
			return _user;
		}
		std::vector<Ingredient> getIngredients()
		{
			return _ingredients;
		}
		std::vector<std::string> getSteps()
		{
			return _steps;
		}
		unsigned int getNumberOfSteps()
		{
			return _numberOfSteps;
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
					std::cout << "- ";
					_ingredients[i].ingredientOut();
				}
				std::cout << std::endl << "Шаги приготовления: " << std::endl;
				for (size_t i = 0; i < _steps.size(); i++)
				{
					std::cout << i + 1 << ". " << _steps[i] << std::endl;
				}
				std::cout << "Рецепт добавлен пользователем: " << _user.getNickname() << std::endl;
			}
		}
	};

private:
	std::string _name;
	Recipe _recipe;

public:
	Dish() = default;
	Dish(std::string name) : _name(name), _recipe(Recipe()) {}
	void addRecipe(const User& user, const unsigned int& numberOfSteps, const std::vector<std::string>& steps, const std::vector<Ingredient>& ingredients)
	{
		if (_recipe.getNumberOfSteps() == NULL)
			_recipe = Recipe(user, numberOfSteps, steps, ingredients);
		else
			std::cout << "Рецепт уже существует" << std::endl;
	}

	void showDish()
	{
		std::cout << "------------------------" << std::endl;
		std::cout << _name << std::endl << "Рецепт приготовления:" << std::endl;
		if (_recipe.getNumberOfSteps() != NULL)
			_recipe.recipeOut();
		else
			std::cout << "Рецепт еще не добавлен" << std::endl;
		std::cout << "------------------------" << std::endl;
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
	User me("HeyYO");
	Dish fish("Жаренная рыба");
	fish.showDish();
	fish.addRecipe(me, 0, { "Пожарить горбушу", "Посолить" }, { Ingredient("Соль"), Ingredient("Горбуша") });
	fish.showDish();
	fish.addRecipe(me, 2, { "Пожарить горбушу", "Посолить" }, { Ingredient("Соль"), Ingredient("Горбуша") });
	fish.showDish();
	/*Recipe Tort;
	Tort.setNumberOfSteps(1);
	Tort.setSteps({ "asdasd" });
	Tort.addIngredient("Молоко");
	Tort.addIngredient("Говядина");
	Tort.addIngredient("Рисовая мука");
	Tort.recipeOut();

	Tort.addIngredient("Что-то");
	Tort.recipeOut();*/
	return 0;
}
