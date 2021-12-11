#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <fstream>
#include <chrono>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>

namespace DT
{
	namespace Optimization
	{
		extern std::string RED;
		extern std::string BLUE;
		extern bool track;

		struct BlockStruct
		{
			std::string color;
			std::string name;
			float time;

			bool operator <(const BlockStruct& d);

			bool operator >(const BlockStruct& d);
		};

		class BlockSpace {
		private:
			std::vector<BlockStruct> result;

		public:
			template<typename F, typename... Args>
			void Block(std::string _name, std::string _color, F func, Args&&... args){
				if(!track) return;
				
			    std::chrono::high_resolution_clock::time_point t1=std::chrono::high_resolution_clock::now();
			    func(std::forward<Args>(args)...);
			    BlockStruct b;
			    b.name = _name;
			    b.color = _color;
			    b.time = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()-t1).count()/1e+9;
			    result.push_back(b);
			}

			void Export(bool sorted);
		};
	}
}

#endif