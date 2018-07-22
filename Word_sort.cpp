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
	if (m_files.size() == 0)std::cout << "nill";
	if (m_files.size() >= 1) 
	{
		ThreadPool m_pool = SingleThreadPool::get_pool(10);
 	Sort_alg sort_alg ;
	sort_alg = get_algorithm_sor();

	

	
		for ( size_t i = 0; i < m_files.size(); i++)
		{
			if (i > m_files.size())break;
			/*	m_files.at(i)->read_to_end(words);
			split.set_string(words);
			m_files.at(i)->rewrite_file(words);*/
			//	std::cout << "sort all";
			std::string path = m_files[i];

			m_pool.run_async([&,sort_alg]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds(500));
				Split split;
				std::string words;
				File file(path);
				//	std::cout << std::this_thread::get_id()<<std::endl;
				//std::cout << m_files[i] << std::endl;
				file.read_to_end(words);

				split.set_string(words);
			/*	
				while (sort_alg < 1 || sort_alg>4)
				{
					sort_alg = get_algorithm_sor();
				}*/
		std::vector<std::string> v_words = split.get_words();
		std::cout << "alg: " << sort_alg;
				switch (sort_alg)
				{
				case ALPHABETICAL_ORDER_LOW:
					sort(v_words.begin(), v_words.end(), alp_low_order);
					break;
				case ALPHABETICAL_ORDER_UP:
					sort(v_words.begin(), v_words.end(), alp_up_order);
					break;
				case LEN_ORDER_LOW:
					sort(v_words.begin(), v_words.end(), len_low_order);
					break;
				case LEN_ORDER_UP:
					sort(v_words.begin(), v_words.end(), len_up_order);
					break;
				default:
					std::cout << "default";
					break;

				}
		//		sorting(&v_words, &sort_alg);
		//		sort(v_words.begin(), v_words.end(), alp_low_order);
				words = "";
				/*for (auto el: v_words)
				{
				std::cout << " " << el;
				}*/
				for (auto &word : v_words)
				{
					words += word + " ";
				}

				file.rewrite_file(words);

			});
			//std::this_thread::sleep_for(std::chrono::milliseconds(500));


		}
	}
	

}




