#include "percepClass.h"

bool is_empty(std::ifstream& pFile)																						//Проверка на пустоту файла
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

std::vector<std::vector<std::vector<int>>> number = {																	//Эталоны
	{ {1, 1, 1},
	  {1, 0, 1},
	  {1, 0, 1},
	  {1, 0, 1},
	  {1, 1, 1} },

	{ {0, 1, 0},
	  {1, 1, 0},
	  {0, 1, 0},
	  {0, 1, 0},
	  {0, 1, 0} },

	{ {1, 1, 1},
	  {0, 0, 1},
	  {1, 1, 1},
	  {1, 0, 0},
	  {1, 1, 1} },

	{ {1, 1, 1},
	  {0, 0, 1},
	  {1, 1, 1},
	  {0, 0, 1},
	  {1, 1, 1} },

	{ {1, 0, 1},
	  {1, 0, 1},
	  {1, 1, 1},
	  {0, 0, 1},
	  {0, 0, 1} },

	{ {1, 1, 1},
	  {1, 0, 0},
	  {1, 1, 1},
	  {0, 0, 1},
	  {1, 1, 1} },

	{ {1, 1, 1},
	  {1, 0, 0},
	  {1, 1, 1},
	  {1, 0, 1},
	  {1, 1, 1} },

	{ {1, 0, 1},
	  {0, 0, 1},
	  {1, 1, 1},
	  {1, 0, 0},
	  {1, 0, 0} },

	{ {1, 1, 1},
	  {1, 0, 1},
	  {1, 1, 1},
	  {1, 0, 1},
	  {1, 1, 1} },

	{ {1, 1, 1},
	  {1, 0, 1},
	  {1, 1, 1},
	  {0, 0, 1},
	  {1, 1, 1} },
};

int main()																																
{																												
	std::ifstream is("weights.txt");

	std::setlocale(LC_ALL, "Russian");

	std::vector<percep> perceps;

	for (int i = 0; i < 10; ++i)																						//Создание и обучение персептронов			
	{
		percep Perceptron = percep(number[i]);

		if (is_empty(is))
		{
			Perceptron.fillWeight();
			Perceptron.train();
		}
		else
		{	
			std::vector<std::vector<double>> temp = std::vector<std::vector<double>>(5, std::vector<double>(3));

			for (int i = 0; i < 5; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					is >> temp[i][j];
				}
			}

			Perceptron.WW = temp;
			Perceptron.train();
		}
		
		perceps.push_back(Perceptron);
	}

	is.close();

	std::ofstream fs("weights.txt");
	for (int i = 0; i < perceps.size(); ++i)																			//Вывод результатов
	{
		
		std::vector<double> var;
		for (int j = 0; j < perceps.size(); ++j)
		{
			double h = perceps[i].procOutputSignal(perceps[i].inputSignal(number[j]));
			var.push_back(h);
		}

		for (int j = 0; j < var.size(); ++j)
		{
			std::cout << "Персептрон: " << i << " " << "Выходной сигнал: " << var[j] << " " << "Число: " << j << std::endl;
		}
		std::cout << "\n";

		for (auto j : perceps[i].WW)
		{
			for (int k = 0; k < j.size(); ++k)
			{
				fs << j[k] << " ";
			}
		}
		fs << "\n";
	}
}