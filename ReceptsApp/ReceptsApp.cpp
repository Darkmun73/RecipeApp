#include <iostream>
#include <vector>
#include <string>
#include "Container.cpp"

template<typename T, size_t n>
inline size_t arraySize(const T(&arr)[n])
{
	return n;
}

const std::string nameOfAllIngredientsInGramms[5] = { "Пшеничная мука", "Соль", "Сахар", "Moloko", "Масло" };
const std::string nameOfAllIngredientsInNumber[5] = { "Куриное яйцо", "Яблоко", "Морковь", "Баклажан", "Клубника" };

class Category;
MyBidirectionalList<Category> allCategories;


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
class Category
{
private:
	std::string _name;
	std::vector<std::string> _ingredients;
public:
	Category() : _name("nonameCategory"), _ingredients(std::vector<std::string>()) { }
	Category(std::string name) : _name(name), _ingredients(std::vector<std::string>()) { }
	Category(std::string name, std::vector<std::string> ingredients) : _name(name), _ingredients(ingredients) { }
	~Category() {}

	void setName(std::string name)
	{
		_name = name;
	}

	std::string getName()
	{
		return _name;
	}

	std::vector<std::string>& getIngredients() //надеюсь то, что я сделал геттер с ссылкой, это норма
	{
		return _ingredients;
	}
};

class Ingredient
{
private:
	std::string _name;
	Category _category;
public:
	Ingredient(std::string name)
	{
		MyBidirectionalList<Category>::iterator iter;

		//Среди всех категорий из allCategories ищу ту, в которой есть имя name ингредиента.
		iter = std::find_if(allCategories.begin(), allCategories.end(),
			[name](Category categ)
			{
				return std::find(categ.getIngredients().begin(), categ.getIngredients().end(), name) != categ.getIngredients().end();
			}
		); 
		
		//Если такая категория есть, то...
		if (iter != allCategories.end())
		{
			_name = name;
			_category = *iter;
		}
		else //если - нет, то...
		{
			_name = "nonameIngredient";
		}
	}

	std::string getName()
	{
		return _name;
	}

	Category getCategory()
	{
		return _category;
	}

	void ingredientOut()
	{
		std::cout << std::endl << _name << std::endl << _category.getName() << std::endl;
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

int main()
{
	setlocale(LC_ALL, "ru");
	allCategories.push_back(Category("Molochnie produkty", { "Moloko", "Maslo", "Cheese" }));
	Ingredient a("asd");
	std::cout << a.getName() << " " << a.getCategory().getName() << std::endl;
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
//узнать про cout в методах класса