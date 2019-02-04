#include "GA.h"

GA::GA(double d[][2], size_t drow, int rdx)
{
	radix = rdx;
	for(int i = 0; i < drow; i++)
		addDomain(d[i][0], d[i][1]);
    srand(time(NULL));
}

GA::~GA() {}

void GA::addDomain(double start, double end)
{
	std::vector<double> sd;
	sd.push_back(start);
	sd.push_back(end);
	domain.push_back(sd);
}

void GA::init(std::string &c)
{
    for(int i = 0; i < c.length(); i++)
        c[i] = rand() % 2 + '0';
    return;
}

int GA::random(std::string c)
{
	return rand() % c.length();
}

void GA::mutation(std::string &c)
{
	int m = random(c);
	c[m] = c[m] == '0' ? '1' : '0';
	return;
}

void GA::crossover(std::string &c1, std::string &c2)
{
	int m = random(c1);
	std::string tc1 = c1.substr(m);
	std::string tc2 = c2.substr(m);
	c1.replace(m, c1.length() - m, tc2);
	c2.replace(m, c2.length() - m, tc1);
	return;
}

int GA::countCromosome()
{
	double sum = 0;
	for(int j = 1; j <= domain.size(); j++)
		sum += population(j);
	return (int)sum;
}

double GA::population(int i)
{
	return ceil(log((domain[i-1][1] - domain[i-1][0]) * pow(10.0, radix)) / log(2.0));
}

long int GA::bindec(std::string c)
{
	signed long p = c.length() - 1;
	long int dec = 0;
	while(p >= 0)
	{
		dec += ( c[p] - '0' ) * pow(2, c.length() - p - 1);
		p--;
	}
	return dec;
}

double GA::splitObject(std::string c, int n)
{
	int ma = 0;
	for(int i = 1; i < n; i++)
		ma += population(i);
	int mb = population(n);
	return binreal(c.substr(ma, mb), domain[n-1][0], domain[n-1][1]);
}

double GA::binreal(std::string c, double a, double b)
{
	return a + bindec(c) * ( b - a ) / ( pow(2, c.length() ) - 1 );
}
