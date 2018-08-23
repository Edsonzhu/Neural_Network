#include "Neuron.h"

Neuron::Neuron(int matrixLine, int matrixCol)
{
   srand(1);
   for (unsigned int x = 0; x < matrixLine; x++) //initializing
   {
      syn0.push_back(std::deque<double>());
      for (unsigned int j = 0; j < matrixCol; j++) // genarate random numbers
      {
         syn0[x].push_back(-1 + 2 * rand() / ((double)RAND_MAX)); //from -1 to 1
         if (x == 0)//condition to create a vector of size matrixCol
         {
            syn1.push_back(-1 + 2 * rand() / ((double)RAND_MAX));
         }
      }
   }
}

Neuron::~Neuron()
{
   syn0.clear();
   syn1.clear();
}

std::deque<std::deque<double>> Neuron::getTransRow(std::deque<std::deque<double>>& matr2d)
{
   std::deque<std::deque<double>> holder;
   for (unsigned int i = 0; i < matr2d[0].size(); i++)
   {
      holder.push_back(std::deque<double>());
   }
   for (std::deque<std::deque<double>>::iterator it = matr2d.begin(); it != matr2d.end(); it++)
   {
      for (std::pair <std::deque<double>::iterator, std::deque<std::deque<double>>::iterator> jit(it->begin(), holder.begin());
         jit.first != it->end(); jit.first++, jit.second++)
      {
         jit.second->push_back(*jit.first);
      }
   }
   return (holder);
}

std::deque<std::deque<double>> Neuron::getTransRow(std::deque<double> & first)
{
   std::deque<std::deque<double>> holder;
   for (std::pair <std::deque<double>::iterator, int> it(first.begin(), 0); it.first != first.end(); it.first++, it.second++)
   {
      holder.push_back(std::deque<double>());
      holder[it.second].push_back(*it.first);
   }
   return(holder);
}

double Neuron::dot(std::deque<double>& first, std::deque<double>& second)
{
   return (std::inner_product(first.begin(), first.end(), second.begin(), 0.));
}

std::deque<double> Neuron::dot(std::deque<std::deque<double>> & first, std::deque<double> & second)
{
   std::deque<double> holder;
   for (std::deque<std::deque<double>>::iterator it = first.begin(); it != first.end(); it++)
   {
      holder.push_back(dot(*it, second));
   }
   return (holder);
}

std::deque<std::deque<double>> Neuron::dot(std::deque<std::deque<double>> & lines, std::deque<std::deque<double>> & col)
{
   std::deque<std::deque<double>> holder;
   std::deque<std::deque<double>> ColTrans;
   if (col[0].size() == 1)
   {
      ColTrans = col;
   }
   else
   {
      ColTrans = getTransRow(col);
   }
   for (std::deque<std::deque<double>>::iterator it = lines.begin(); it != lines.end(); it++)
   {
      holder.push_back(dot(ColTrans, *it));
   }
   return (holder);
}

std::deque<double> Neuron::thinking(std::deque<std::deque<double>>& first2d, std::deque<double>& second)
{
   std::deque<double> holder;
   std::deque<double> dotResul = dot(first2d, second);
   for (std::deque<double>::iterator it = dotResul.begin(); it != dotResul.end(); it++)
   {
      holder.push_back(1 / (1 + (exp(-(*it)))));
   }
   return (holder);
}

std::deque<std::deque<double>> Neuron::thinking(std::deque<std::deque<double>> & first2dInput, std::deque<std::deque<double>> & second2d)
{
   std::deque<std::deque<double>> holder;
   std::deque<std::deque<double>> dotResult = dot(first2dInput, second2d);
   int i = 0;
   for (std::deque<std::deque<double>>::iterator it = dotResult.begin(); it != dotResult.end(); it++)
   {
      holder.push_back(std::deque<double>());
      for (std::deque<double>::iterator secondIt = it->begin(); secondIt != it->end(); secondIt++)
      {
         holder[i].push_back(1 / (1 + (exp(-(*secondIt)))));
      }
      i++;
   }
   return (holder);
}

std::deque<double> Neuron::error(std::deque<double> & outputTraining, std::deque<double> & second)
{
   std::deque<double> holder;
   for (std::pair <std::deque<double>::iterator, std::deque<double>::iterator>
      it(outputTraining.begin(), second.begin()); it.first != outputTraining.end(); it.first++, it.second++)
   {
      holder.push_back(((*it.first) - (*it.second))*((*it.second) * (1 - (*it.second))));
   }
   return (holder);
}

std::deque<std::deque<double>> Neuron::error(std::deque<double> & l2Error, std::deque<double> & sy1, std::deque<std::deque<double>> & l1)
{
   std::deque<std::deque<double>> holder;
   std::deque<std::deque<double>> l2ErrorTrans = getTransRow(l2Error);
   std::deque<std::deque<double>> sy1Trans = getTransRow(sy1);
   std::deque<std::deque<double>> dotResult = dot(l2ErrorTrans, sy1Trans);
   int i = 0;
   for (std::pair <std::deque<std::deque<double>>::iterator, std::deque<std::deque<double>>::iterator>
      it(dotResult.begin(), l1.begin()); it.first != dotResult.end(); it.first++, it.second++)
   {
      holder.push_back(std::deque<double>());
      for (std::pair <std::deque<double>::iterator, std::deque<double>::iterator>
         jit(it.first->begin(), it.second->begin()); jit.first != it.first->end(); jit.first++, jit.second++)
      {
         holder[i].push_back((*jit.first) * ((*jit.second) * (1 - (*jit.second))));
      }
      i++;
   }
   return (holder);
}

void Neuron::adjustmentSyn0(std::deque<std::deque<double>> & inputTrainin, std::deque<std::deque<double>> & l1Error)
{
   std::deque<std::deque<double>> inputTrainTrans = getTransRow(inputTrainin);
   std::deque<std::deque<double>> dotResult = dot(inputTrainTrans, l1Error);
   for (std::pair <std::deque<std::deque<double>>::iterator, std::deque<std::deque<double>>::iterator>
      it(syn0.begin(), dotResult.begin()); it.second != dotResult.end(); it.first++, it.second++)
   {
      for (std::deque<double>::iterator jit = it.second->begin(); jit != it.second->end(); jit++)
      {
         it.first->push_back(it.first->front() + *jit);
         it.first->pop_front();
      }
   }
}

void Neuron::adjustmentSyn1(std::deque<std::deque<double>> & l1, std::deque<double> & l2Error)
{
   std::deque<std::deque<double>> l1Trans = getTransRow(l1);
   std::deque<double> dotResult = dot(l1Trans, l2Error);

   for (std::deque<double>::iterator it = dotResult.begin(); it != dotResult.end(); it++)
   {
      syn1.push_back(syn1.front() + *it);
      syn1.pop_front();
   }
}

void Neuron::show(std::deque<double> deque)
{
   std::cout << "[ ";
   for (std::deque<double>::const_iterator it = deque.begin(); it != deque.end(); it++)
   {
      std::cout << "[ " << *it << " ]" << std::endl;
   }
   std::cout << " ]" << std::endl;
   std::cout << "Done" << std::endl;
}

void Neuron::show(std::deque<std::deque<double>> deque)
{
   std::cout << "[ ";
   for (std::deque<std::deque<double>>::const_iterator it = deque.begin(); it != deque.end(); it++)
   {
      std::cout << "[ ";
      for (std::deque<double>::const_iterator hit = it->begin(); hit != it->end(); hit++)
      {
         std::cout << *hit << "  ";
      }
      std::cout << " ]" << std::endl;
   }
   std::cout << " ]" << std::endl;
   std::cout << "Done" << std::endl;
}

void Neuron::train(unsigned int times, std::deque<std::deque<double>> & trainInput, std::deque<double> & trainOutput)
{
   std::deque<std::deque<double>> l1;
   std::deque<double> l2;
   std::deque<std::deque<double>> l1Error;
   std::deque<double> l2Error;
   for (int i = 0; i < times; i++)
   {
      l1.clear();
      l2.clear();
      l2Error.clear();
      l1Error.clear();
      l1 = this->thinking(trainInput, syn0);
      l2 = this->thinking(l1, syn1);
      l2Error = this->error(trainOutput, l2);
      l1Error = this->error(l2Error, syn1, l1);
      this->adjustmentSyn1(l1, l2Error);
      this->adjustmentSyn0(trainInput, l1Error);
   }

   std::cout << "syn0" << std::endl;
   show(syn0);
   std::cout << "syn1" << std::endl;
   show(syn1);
   //std::cout << "l1" << std::endl;
   //show(l1);
   //std::cout << "l2" << std::endl;
   //show(l2);
   //std::cout << "l2Error" << std::endl;
   //show(l2Error);
   //std::cout << "l1Error" << std::endl;
   //show(l1Error);

}