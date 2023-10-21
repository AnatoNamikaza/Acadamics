#include <fstream>
#include <iostream>
#include <string.h>
#include <pthread.h>

using namespace std;

void* remove_dup_and_neg(void* filename)
{

	string file = *reinterpret_cast<std::string*>(filename);
	ifstream fin(file);

	if (!fin.is_open())
	{
		cout << "File not found / could not be opened! (-_-)\n";
		return NULL;
	}

	int	temp = 0,
		totalValues = 0,
		negativeValues = 0;

	while (!fin.eof())
	{
		fin >> temp;
		totalValues++;
		if (temp < 0)
			negativeValues++;
	}

	totalValues -= negativeValues;
	int index = 0, size = 0, Again = 0,
		* buffer = new int[totalValues] {0};

	fin.close();

	fin.open(file);

	while (!fin.eof())
	{
		fin >> temp;
		if (temp > -1)
		{
			for (int i = 0; i < size; i++)
				if (buffer[i] == temp)
					Again = 1;

			if (Again > 0)
			{
				Again = 0;
				continue;
			}

			buffer[index] = temp;

			index++, size++;
		}
	}

	int* unique_buffer = new int[size + 1]{ 0 };

	for (int i = 0; i < size; i++)
		unique_buffer[i] = buffer[i];
	unique_buffer[size] = -1;

	//for (int i = 0; i < size+1; i++)
	//	cout << unique_buffer[i] << '\n';
	//cout << "\n------------------------------\n";
	delete[] buffer, buffer = nullptr;

	fin.close();

	return (void*)unique_buffer;
}

int main()
{
	string filename[2] = { "f1.txt", "f2.txt" };
	pthread_t id[2];

	if (pthread_create(&id[0], NULL, &remove_dup_and_neg, &filename[0]) == -1 ||
		pthread_create(&id[1], NULL, &remove_dup_and_neg, &filename[1]) == -1)
	{

		cout << "Creation of threads failed! (-_-)\n";
		return 1;
	}

	int* uniqueBuffer1 = NULL, * uniqueBuffer2 = NULL;
	pthread_join(id[0], (void**)&uniqueBuffer1);
	pthread_join(id[1], (void**)&uniqueBuffer2);

	if (uniqueBuffer1 && uniqueBuffer2)
	{
		int totalValues = 0, sum = 0;

		for (int i = 0; uniqueBuffer1[i] != -1; i++, totalValues++)
			sum += uniqueBuffer1[i];

		for (int i = 0; uniqueBuffer2[i] != -1; i++, totalValues++)
			sum += uniqueBuffer2[i];
		cout << "-----------------------------------\n"
			<< "Total values in both files:\t" << totalValues << '\n'
			<< "Average of both files:\t\t" << sum / totalValues << '\n'
			<< "-----------------------------------\n";
		delete[] uniqueBuffer1, delete[] uniqueBuffer2;
		uniqueBuffer1 = nullptr, uniqueBuffer2 = nullptr;
	}

	else
	{
		cout << "int array(s) not found in file (-_-)";
		return 1;
	}

	return 0;
}
