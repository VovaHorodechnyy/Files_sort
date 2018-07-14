#pragma once
#include"stdafx.h"

class File 
{
private:
	std::ifstream m_file;
	std::string m_path;
public:
	~File() {}
	File()
	{
		m_path = "";
	}
	File(const std::string&path) 
	{
		m_path = path;
	}
	File(const File& f) 
	{
		m_file.open(f.m_path);
	}
	
	bool read_to_end(std::string &str_out) 
	{
		if (m_path!="") 
		{
			m_file.open(m_path);
			if (str_out != "") { str_out = ""; }
			std::string data;
			while (m_file.good())
			{
				std::getline(m_file, data);
				str_out += data;
			}
			if (m_file.eof()) 
			{ 
				//std::cout << "[EoF reached]\n";
				m_file.close();
				return true; 
			}
				
			else 
			{
				//std::cout << "[error reading]\n";
				m_file.close();
				return false;
			}
				
		}
		
	}
	void rewrite_file(std::string& words) 
	{
		std::ofstream rewrite(m_path);
		rewrite << words;
		rewrite.close();
	
	}
	

};
