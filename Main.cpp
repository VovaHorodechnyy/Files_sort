#include"Word_sort.h"







int main()
{
	//int argc, char*argv[]
	int argc = 1;
	std::string path;
	if (argc == 1) 
	{
		Data_Sort data;
		enter_path:
		std::cout << "Enter path to directory: " << std::endl;
		std::cin >> path;
		if (path == "")goto enter_path;
		
		
		fill_vector(path, &data.v_pair,&data);
		show_n_fill_data_v(&data);
		Word_sort_cmd a;
	}
	else 
	{
		std::vector<std::string>files;
		files.reserve(argc);
		for (size_t i = 1; i < argc; i++)
		{
			//files.push_back(argv[i]);
		}

		///	
		//debug

		//debug
		///
		Word_sort_cmd a(files);
		a.sort_all();
	
	}
	std::cout << "It's all? y(Yes)/n(No)";

	
	



	

	system("pause");
	return 0;
}