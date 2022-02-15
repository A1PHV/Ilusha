#include <bits/stdc++.h>

class percep {																									//����� �����������
private:
	double iS;
	double procOutS;
	bool rA;
	double bias = 0.3;										
	const double CONST = 0.01;
	std::vector<std::vector<std::vector<int>>> standards;
	std::vector<std::vector<int>> numbers;

public:		
	std::vector<std::vector<double>> WW;

	percep()																									//����������� �� ���������
	{

	}

	percep(std::vector<std::vector<std::vector<int>>> standard,
		   std::vector<std::vector<int>> number)																//����������� ������
	{
		WW = std::vector<std::vector<double>>(5, std::vector<double>(3));
		standards = standard;
		numbers = number;

	}

	void fillWeight()																							//���������� �����																	
	{
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				WW[i][j] = 0.5;
			}
		}
	}

	bool takeRightAns(std::vector<std::vector<int>> vi)															//��������� ����������� ������
	{
		if (numbers == vi)
		{
			return true;
		}
		return false;
	}

	double inputSignal(std::vector<std::vector<int>> vi)														//������� ������
	{
		double M = 0;
		for (int i = 0; i < vi.size(); ++i)
		{
			for (int j = 0; j < vi[i].size(); ++j)
			{
				M += WW[i][j] * vi[i][j] + bias;
			}
		}
		return M;
	}

	double procOutputSignal(double h)																			//������� ���������
	{
		return (1 / (1 + exp(-h)));
	}

	void refreshWeight(double& Wi, double rightans, double xi, double procOutS)									//���������� ����
	{
		Wi = Wi + CONST * (1 - procOutS) * procOutS * (rightans - procOutS) * xi;
	}

	void train()																								//���������� �����������
	{
		for (size_t i = 0; i < 1000000; ++i)
		{
			std::vector<std::vector<int>> vi;

			int randomizer = rand() % 10;

			if (!takeRightAns(standards[randomizer]))
			{
				randomizer = rand() % 10;
				vi = standards[randomizer];
			}
			else
			{
				randomizer = rand() % 10;
				vi = standards[randomizer];
			}
			

			/*for (int i = 0; i < 5; ++i)
			{
				std::vector<int> tmp;
				for (int j = 0; j < 3; ++j)
				{
					tmp.push_back(rand() % 100 > 50 ? -1 : 1);
				}
				vi.push_back(tmp);
			}*/

			iS = inputSignal(vi);
			procOutS = procOutputSignal(iS);
			rA = takeRightAns(vi);

			//if (randomizer > 0)
			//{
			//	iS = inputSignal(vi);
			//	procOutS = procOutputSignal(iS);
			//	rA = takeRightAns(vi);
			//}
			//else
			//{
			//	iS = inputSignal(standards);
			//	procOutS = procOutputSignal(iS);
			//	rA = takeRightAns(standards);
			//}
			
			for (int i = 0; i < 5; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					refreshWeight(WW[i][j], rA, vi[i][j], procOutS);
				}
			}
		}
	}
};


