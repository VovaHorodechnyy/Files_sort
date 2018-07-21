#include"stdafx.h"
class Split 
{
private:
	std::vector<std::string>m_words;
	std::string m_string;
	std::string m_separator;
	size_t m_prev = 0;
	size_t m_next;
	size_t m_delta;
	void clear_vector() 
	{
		m_words.clear();
		m_words.reserve(25);
	}
public:
	Split():m_separator(" "),m_delta(m_separator.length()) {}
	Split(std::string& str, std::string separator) :m_string(str), m_separator(separator), m_delta(m_separator.length()) {}
	void set_separator(std::string&separator) 
	{
		m_separator = separator;
		m_delta = m_separator.length();
	
	}
	void set_string(std::string&string)
	{
		m_string = string;

	}
	std::vector<std::string>&get_words() 
	{
		while ((m_next = m_string.find(m_separator, m_prev)) != std::string::npos) {
			std::string tmp = m_string.substr(m_prev, m_next - m_prev);
			m_words.push_back(m_string.substr(m_prev, m_next - m_prev));
			m_prev = m_next + m_delta;
		}
		std::string tmp = m_string.substr(m_prev);
		//std::cout << tmp << std::endl;
		m_words.push_back(m_string.substr(m_prev));
	
		return m_words;
	}
	void get_words(std::vector<std::string> *data_words)
	{
		while ((m_next = m_string.find(m_separator, m_prev)) != std::string::npos) {
			std::string tmp = m_string.substr(m_prev, m_next - m_prev);
			data_words->push_back(m_string.substr(m_prev, m_next - m_prev));
			m_prev = m_next + m_delta;
		}
		std::string tmp = m_string.substr(m_prev);
		//std::cout << tmp << std::endl;
		data_words->push_back(m_string.substr(m_prev));

	}
};
