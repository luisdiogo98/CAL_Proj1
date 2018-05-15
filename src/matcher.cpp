/*
 * matcher.cpp
 */
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>

#define MAX_LENGTH 100

using namespace std;

void computeLPS(string pat, int M, int *lps)
{
	int len = 0;
	int i = 1;

	lps[0] = 0;

	while (i < M)
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len)
				len = lps[len - 1];

			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

int kmpMatcher(string text, string pattern) 
{
	int count = 0;

	int m = pattern.length();
	int n = text.length();

	int lps[MAX_LENGTH];

	computeLPS(pattern, m, lps);

	int i = 0;
	int j = 0;
	while (i < n)
	{
		if (pattern[j] == text[i])
		{
			j++;
			i++;
		}

		if (j == m)
		{
			count++;
			j = lps[j - 1];
		}

		else if (i < n && pattern[j] != text[i])
		{
			if (j)
				j = lps[j - 1];

			else i++;
		}
	}

	return count;
}


int numStringMatching(string filename,string toSearch) 
{
	int count = 0;
	ifstream file(filename);

	while (!file.eof())
	{
		getline(file, filename);

		count += kmpMatcher(filename, toSearch);
	}

	return count;
}

int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

int editDistance(string pattern, string text) 
{
	int distance[MAX_LENGTH];

	for (int j = 0; j <= text.length(); j++)
		distance[j] = j;

	int old;
	int novo;

	for (int i = 1; i <= pattern.length(); i++)
	{
		old = distance[0];
		distance[0] = i;

		for (int j = 1; j <= text.length(); j++)
		{
			if (pattern[i - 1] == text[j - 1])
				novo = old;

			else novo = 1 + min(old, distance[j], distance[j - 1]);

			old = distance[j];
			distance[j] = novo;
		}
	}

	return distance[text.length()];
}

float numApproximateStringMatching(string filename,string toSearch) 
{
	float dist = 0;
	float words = 0;
	ifstream file(filename);
	string temp;

	while (!file.eof())
	{
		getline(file, filename);
		std::stringstream ss(filename);

		while (ss.good())
		{
			getline(ss, temp, ' ');
			dist += editDistance(temp, toSearch);
			words++;
		}
	}

	return dist/words;
}
