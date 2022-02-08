#include <bits/stdc++.h>

class percep {																									//����� �����������
private:
	double iS;
	double procOutS;
	bool rA;
	double bias = 0;										
	const double CONST = 0.1;
	std::vector<std::vector<int>> standards;

public:		
	std::vector<std::vector<double>> WW;

	percep()																									//����������� �� ���������
	{

	}

	percep(std::vector<std::vector<int>> standard)																//����������� ������
	{
		WW = std::vector<std::vector<double>>(5, std::vector<double>(3));
		standards = standard;
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
		if (standards == vi)
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
			int randomizer = rand() % 3;


			std::vector<std::vector<int>> vi;
			for (int i = 0; i < 5; ++i)
			{
				std::vector<int> tmp;
				for (int j = 0; j < 3; ++j)
				{
					tmp.push_back(rand() % 2);
				}
				vi.push_back(tmp);
			}

			if (randomizer < 1)
			{
				iS = inputSignal(vi);
				procOutS = procOutputSignal(iS);
				rA = takeRightAns(vi);
			}

			else
			{
				iS = inputSignal(standards);
				procOutS = procOutputSignal(iS);
				rA = takeRightAns(standards);
			}
			

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


