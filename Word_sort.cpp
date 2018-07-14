#include "Word_sort.h"
Word_sort_cmd::Word_sort_cmd( std::vector<std::string>files )
{
	
	for (int  i = 0; i < files.capacity(); ++i)
	{  
		
	
		m_files.push_back(files[i]);
	
	}


}
void Word_sort_cmd::sort_all()
{
	
	ThreadPool m_pool = SingleThreadPool::get_pool(10);
	auto sort_alg = get_algorithm_sor();
	auto order = change_alg(sort_alg);
	for (size_t i = 0; i < m_files.capacity(); ++i)
	{

	/*	m_files.at(i)->read_to_end(words);
		split.set_string(words);
		m_files.at(i)->rewrite_file(words);*/
	//	std::cout << "sort all";
	//	std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
		m_pool.run_async([&]()
		{
			//std::this_thread::sleep_for(std::chrono::milliseconds(500));
			Split split;
			std::string words;
			File file(m_files[i]);
		//	std::cout << std::this_thread::get_id()<<std::endl;
			//std::cout << m_files[i] << std::endl;
			file.read_to_end(words);

			split.set_string(words);

			auto v_words = split.get_words();
			
			sort(v_words.begin(), v_words.end(), order);
			words = "";
			/*for (auto el: v_words)
			{
				std::cout << " " << el;
			}*/
			for (auto &word : v_words) 
			{
				words += word+" ";
			}
			
			file.rewrite_file(words);

		});
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	
	
	}

}



