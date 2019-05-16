#include <iostream>
#include <vector>
#include <map>
#include <string>
#include<sstream>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>

#include <xlnt/xlnt.hpp>

using namespace std;

int main(int argc, char const *argv[])
{
	//不完美 中文目前还有问题
	xlnt::workbook wb;
	wb.load("/Users/wangyiming/Downloads/bug.xlsx");

	auto ws = wb.active_sheet();
	xlnt::font run_font;
	run_font.name("SimSun");

	std::vector< std::vector<std::string> > theWholeSpreadSheet;

	for (auto row : ws.rows())
	{
		ws.rows().font(run_font);
		std::vector<std::string> aSingleRow;
	
		for (auto cell : row)
		{	
			 auto ssss = cell.value<std::string>();
			 aSingleRow.push_back(ssss);
		}
		theWholeSpreadSheet.push_back(aSingleRow);
	}
	std::clog << "Processing complete" << std::endl;
	std::clog << "Reading the vector and printing output to the screen" << std::endl;
	for (int rowInt = 0; rowInt < theWholeSpreadSheet.size(); rowInt++)
	{
		for (int colInt = 0; colInt < theWholeSpreadSheet.at(rowInt).size(); colInt++)
		{
			string s = theWholeSpreadSheet.at(rowInt).at(colInt);

			std::cout <<s <<" ";
		}
		std::cout << endl;
	}
	return 0;
}





