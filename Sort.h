#pragma once



	static bool alp_low_order(const std::string& f, const std::string& s)
	{
		return   f < s;
	}
	static bool alp_up_order(const std::string& f, const std::string& s)
	{

		return   f > s;
	}
	static bool len_low_order(const std::string& f, const std::string& s)
	{
		return  f.length()<s.length();
	}
	static bool len_up_order(const std::string& f, const std::string& s)
	{
		return  f.length()>s.length();
	}
	static void sort(std::vector<std::string>&data, bool(*func)(const std::string& f, const std::string& s))
	{

		std::sort(data.begin(), data.end(), func);
	}
	 enum Sort_alg
	{
		ALPHABETICAL_ORDER_LOW = 1,
		ALPHABETICAL_ORDER_UP,
		LEN_ORDER_LOW,
		LEN_ORDER_UP
	};
	 volatile	 static Sort_alg get_algorithm_sor()
	{
	 menu:

		 std::cout << "\n Order:\n"
			 << "ALPHABETICAL_ORDER_LOW - 1\n"
			 << "ALPHABETICAL_ORDER_UP - 2\n"
			 << "LEN_ORDER_LOW - 3\n"
			 << "LEN_ORDER_UP - 4\n";

		 int change;
		 std::cin >> change;

		 if (change < 1 || change>4)
			 goto menu;

		 if (change == 1)
			 return Sort_alg::ALPHABETICAL_ORDER_LOW;
		 if (change == 2)
			 return Sort_alg::ALPHABETICAL_ORDER_UP;
		 if (change == 3)
			 return Sort_alg::LEN_ORDER_LOW;
		 if (change == 4)
			 return Sort_alg::LEN_ORDER_UP;
	
	}
	   static 	 bool (*change_alg(Sort_alg alg))(const std::string&, const std::string&)
{
		    bool(*order)(const std::string& f, const std::string& s);
	order = alp_low_order;
	switch (alg)
	{
	case ALPHABETICAL_ORDER_LOW:
		order = alp_low_order;
		break;
	case ALPHABETICAL_ORDER_UP:
		order = alp_up_order;
		break;
	case LEN_ORDER_LOW:
		order = len_low_order;
		break;
	case LEN_ORDER_UP:
		order = alp_low_order;
		break;
	
	}
	
	//bool(*order)(const std::string& f, const std::string& s) = alp_low_order;
	//order = alp_low_order;

	return order;
}

	  
