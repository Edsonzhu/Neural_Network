#ifndef _NEURON_H_
#define _NEURON_H_

#include <deque>
#include <iostream>
#include <random>
#include <numeric>
#include <cmath>

class Neuron
{
public:
   Neuron(int matrixLine, int matrixCol);
   ~Neuron();
   void show(std::deque<double> deque);
   void show(std::deque<std::deque<double>> deque);
   void train(unsigned int times, std::deque<std::deque<double>> & trainInput, std::deque<double> & trainOutput);

protected:
   std::deque<std::deque<double>> getTransRow(std::deque<std::deque<double>> & matr2d);
   std::deque<std::deque<double>> getTransRow(std::deque<double> & first);
   double dot(std::deque<double> & first, std::deque<double> & second);
   std::deque<double> dot(std::deque<std::deque<double>> & first, std::deque<double> & second);
   std::deque<std::deque<double>> dot(std::deque<std::deque<double>> & first, std::deque<std::deque<double>> & second);
   std::deque<double> thinking(std::deque<std::deque<double>> & first2d, std::deque<double> & second);
   std::deque<std::deque<double>> thinking(std::deque<std::deque<double>> & first2dInput, std::deque<std::deque<double>> & second2d);
   std::deque<double> error(std::deque<double> & outputTraining, std::deque<double> & second);
   std::deque<std::deque<double>> error(std::deque<double> & l2Error, std::deque<double> & sy1, std::deque<std::deque<double>> & l1);
   void adjustmentSyn0(std::deque<std::deque<double>> & inputTrainin, std::deque<std::deque<double>> & l1Error);
   void adjustmentSyn1(std::deque<std::deque<double>> & l1, std::deque<double> & l2Error);

private:
   std::deque<std::deque<double>> syn0;
   std::deque<double> syn1;
};

#endif // !_NEURON_H_
