#pragma once
#include"Stdafx.h"
#include"Split.h"
#include"Read_file.h"
#include"Sort.h"
#include"ThreadPool.h"

struct Data_Sort
{
	std::vector<std::string> files;
	std::string files_str;
	std::vector<std::pair<int, std::string>>v_pair;

};

class Word_sort_cmd
{

private:
	std::vector<std::string> m_files;

	std::string m_alg;
	

public:
    inline 	void fill_vfiles(std::vector<std::string>files)
	{
		m_files.clear();
		for (int i = 0; i < files.capacity(); ++i)
		{
			m_files.push_back(files[i]);

		}
	}
	Word_sort_cmd():m_files(),m_alg() {};
	Word_sort_cmd(std::vector<std::string>files);
	void sort_all();
};

 static void fill_vector(std::string path, std::vector<std::pair<int, std::string>>*files, Data_Sort* data)
{
	data->v_pair.reserve(20);
	int i = 0;
	files->reserve(20);
	for (auto& p : fs::directory_iterator(path)) 
	{
		

		std::string p_ = p.path().string();

		if (p_.substr(p_.length() - 4, 4) == ".txt")
		{
			++i;
			files->push_back(std::make_pair(i, p_));

		}

	}
	//for (auto&elem : files)
	//{
	//	std::cout << elem.first << " " << elem.second;
	//}
	

}

static void show_n_fill_data_v(Data_Sort* data)
{
	std::string numbs_fil;
	std::vector<int> numbsv;
	std::cout << "Enter numbers of files (1,2):"<<std::endl;
	
	

	size_t length =  data->v_pair.size();

	for (size_t i = 0; i < length; i++)
	{
		std::cout << data->v_pair.at(i).first << "  -  " << data->v_pair.at(i).second << std::endl;
	}
	
	std::cin >> numbs_fil;
	
	Split split(numbs_fil, ",");
	split.get_words(&numbsv);

	for (auto &elem : data->v_pair) 
	{
		if (std::find(numbsv.begin(), numbsv.end(), elem.first) != numbsv.end())
		{
			data->files.push_back(elem.second);
		}

	}


	
}
