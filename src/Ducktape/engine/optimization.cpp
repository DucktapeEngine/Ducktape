#include "optimization.h"
using namespace DT;

std::string Optimization::RED = "#EC255A";
std::string Optimization::BLUE = "#08D9D6";
bool Optimization::track = false;

bool Optimization::BlockStruct::operator <(const BlockStruct& d)
{
	if(time < d.time)
	{
		return true;
	}
	return false;
}

bool Optimization::BlockStruct::operator >(const BlockStruct& d)
{
	if(time > d.time)
	{
		return true;
	}
	return false;
}

void Optimization::BlockSpace::Export(bool sorted)
{
	if(!track) return;
	
	if(sorted)
	{
		sort(result.rbegin(), result.rend());
	}

	std::ofstream OutputFile;
	OutputFile.open("output.html", std::ofstream::out | std::ofstream::trunc);

	OutputFile<<"<!DOCTYPE html><html><head><meta charset='utf-8'>	<meta name='viewport' content='width=device-width, initial-scale=1'>	<title>Execution Time Viewer</title>	<link rel='preconnect' href='https://fonts.googleapis.com' />    <link rel='preconnect' href='https://fonts.gstatic.com' crossorigin /><link href='https://fonts.googleapis.com/css2?family=Poppins&display=swap' rel='stylesheet' /><style type='text/css'>* {font-family: Poppins, cursive;}body {padding: 0px;margin: 0px; background-color: #292C6D;}label {padding: 2px;display: inline-block;color: white; margin: 5px; padding-left: 10px; padding-right: 10px;}</style></head><body>";

	for(BlockStruct b:result)
	{
		OutputFile << std::fixed << "<label style='background-color: " << b.color << ";'>" << b.name << ": " << b.time << "</label>";
	}

	OutputFile<<"</body></html>";

	OutputFile.close();
}