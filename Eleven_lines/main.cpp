#include"Neuron.h"
#include<functional>
#include<thread>
const int trainTime = 60000;
using namespace std;
int main(int argc, char *argv[])
{/*
   std::deque<std::deque<double>> trainInput = { { 0,0,1 },{ 0,1,1 },{ 1,0,1 },{ 1,1,1 } };
   std::deque<double>  trainOutput = { 0,1,1,0 };
   Neuron neural_network(trainInput[0].size(), trainInput.size());
   neural_network.train(trainTime, trainInput, trainOutput);
   return 1;*/
   /*
   int d[] = { 1,2,3,4,1,2,3,4,1,2,3,4,1,2,3 };

   //std::cout << sizeof(*d) << std::endl;
   int countt;
   auto count = std::accumulate(d[0], d[15], countt = 0,
      [](auto acc, auto el) {if (!(el & 1)) acc++; std::cout << acc << "  "
      << el << std::endl;  return acc});
   std::cout << count << std::endl;
   */
   template<typename T>
   T runSerial(const T*array, const size_t N, auto doWork)
   {
      T value;
      doWork(0, N, array, value);
      return value;
   }

   template<typename T>
   T runParallel(const T* array, const size_t N, auto doWork)
   {
      int CORES = 3;
      struct 
      {
         function<void(void)> func;
         thread tid;
         T result;
      } table[CORES];
      size_t chunk = (N + CORES - 1) / CORES;
      for (int t = 0; t < CORES; t++)
      {
         size_t start = t * chunk;
      }
   }
}