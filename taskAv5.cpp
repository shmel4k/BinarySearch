// "Полное решение"
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>


int64_t binarySearch(const std::vector<int> &data, const int x, const int k)
{
   int64_t left = data[0];
   int64_t right = INT64_MAX;
 
   int64_t count(0), T(left);
   while (count != k && ((right-left) > 1))
   {
      count = 0;
      T = left + ((right-left) >> 1);
      for(std::vector<int>::const_iterator it = data.begin(); it != data.end() && *it <= T; ++it)
      {
         count += 1 + (T - *it) / x;
      }
      if (count > k)
      {
         right = T;
      }
      else
      {
         left = T;
      }
   }

   return T;
}


int main(int argc, char ** argv)
{
   int N, X, K;
   std::string str;
   std::getline(std::cin, str);
   std::replace_if(str.begin(), str.end(), [](char c){ return c == '\t'; }, ' ');

   std::stringstream ss(str);

   for(int i = 0; std::getline(ss, str, ' ') && i < 3; )
   {
      if (!str.empty())
      {
	 switch (i++)
	 {
	    case 0: N = std::stoi(str);
		    break;
	    case 1: X = std::stoi(str);
                    break;
	    case 2: K = std::stoi(str);
                    break;
	    default: 
		    break;
	 }
      }
   }

   std::vector<int> days; // исходный список дней
   days.reserve(N);

   if (!ss.good())
   {
      ss.clear();
   }
   std::getline(std::cin, str);
   std::replace_if(str.begin(), str.end(), [](char c){ return c == '\t'; }, ' ');
   ss.str(str);
   for(int i = 0; std::getline(ss, str, ' ') && i < N; )
   {
      if(!str.empty())
      {
         days.push_back(std::stoi(str));
         i++;
      }
   }
   std::sort(days.begin(), days.end());


   // удаление дубликатов
   //
   std::unordered_map<int, int> buf; // rest(%) - index
   for(int i = 0; i < days.size(); i++)
   {
      buf.insert(std::pair<int, int>((days[i] - days[0]) % X, i));
   }

   std::vector<int> data; // список дней упорядоченный и без дубликатов
   data.reserve(buf.size());

   for(auto x : buf)
   {
      data.push_back(days[x.second]);
   }
   std::sort(data.begin(), data.end());

//   buf.clear();
//   days.clear();

   const int64_t Day = binarySearch(data, X, K);

   std::vector<int> target;
   target.reserve(data.size());

   for(auto x : data)
   {
      if (x > Day)
      {
        break;
      }
      target.push_back((Day - x) % X);
   }

   std::cout << Day - *std::min_element(target.begin(), target.end()) << std::endl;

   return 0;
}
