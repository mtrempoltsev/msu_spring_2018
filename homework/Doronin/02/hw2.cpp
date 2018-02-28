#include <iostream>
#include <cmath>
#include "numbers.dat"

/*inline bool is_prime(int n)
{
	for(register int i = 2; i <= sqrt(n); ++i)
		if(n % i == 0)
			return false;

	if(n == 0 || n == 1)
		return false;

	return true;
}*/


static bool sieve[Size];

inline void Eratosphen(bool sieve[], const int size)
{
	sieve[0] = sieve[1] = true;
	for(register int p = 2; p < size; p++)
	{
		if(sieve[p] != true && (size_t)p*p < size)
		for(register int j = p*p; j < size; j += p)
			sieve[j] = true;
	}
}

inline int count_prime_numb(const int size, int left, int right, const int array[], bool sieve[]) 
{
	int count = 0;
	int lindex = size;
	int rindex = size;
	
	for(register int i = 0; i < Size; ++i)
		if(array[i] == left)
		{
			lindex = i;
			break;
		}
	
	if(lindex == size)
		return count;
	
	for(register int i = lindex + 1; i < Size; ++i)
		if(array[i] == right)
		{
			rindex = i;
			if(array[i+1] != right)
				break;
		}
						
	if(rindex == size)
		return count;
		
	for(register int i = lindex; i <= rindex; ++i)
		if(!sieve[array[i]]) //we may input: is_prime(array[i])
			count++;
		
	return count;
}



int main(int argc, char* argv[])
{	
	if (((argc - 1)%2 != 0) || (argc == 1))
		return -1;
	
	for(int i = 1; i < argc; i+=2)
	{
		if (std::atoi(argv[i]) > std::atoi(argv[i+1]))
		{
			std::cout<<0<<std::endl;
			return 0;
		}
	}
	
		
	int left=0;
	int right=0;
	
	/*
	 * I suppouse that bool sieve[] initialising all false, and we may economy on it
	 * for(int i = 0; i < Size; ++i)
		sieve[i] = true;
		* 
		* */ 
		
	Eratosphen(sieve, Size);

	
	for(int i = 1; i < argc; i+=2)
	{
		left = std::atoi(argv[i]);
		right = std::atoi(argv[i+1]);
		std::cout<<count_prime_numb(Size, left, right, Data, sieve)<<std::endl;
	}
	
	return 0;
}
