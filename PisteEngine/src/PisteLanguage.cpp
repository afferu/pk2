#include "PisteLanguage.h"

#include <fstream>
#include <string>
#include <stdexcept>

namespace pe
{
	PisteLanguage::PisteLanguage()
		: text_cache_{}
	{
	}

	PisteLanguage::PisteLanguage(StringViewT file_path)
		: PisteLanguage()
	{
		if (!ReadFile(file_path))
		{
			throw std::runtime_error("Unable to read provided file!");
		}
	}

	void PisteLanguage::ParseLine(const std::string_view line_to_parse)
	{
		static constexpr auto BEGIN_KEY = '*', BEGIN_VALUE = ':';

		auto read_key_or_value{ [](auto& read_string, auto& current_iterator, auto end_iterator) {
			while (current_iterator != end_iterator)
			{
				bool finish_reading{ false };
				switch (*current_iterator)
				{
					case BEGIN_KEY:
						finish_reading = true; //Repeated '*'
					break;
					case BEGIN_VALUE:
						finish_reading = true; //Repeated ':'
					break;
					case '\t': break; //omit tab 
					case '\v': break; //omit vert tab
					default:
						read_string += *current_iterator;
						break;
				}
				if (finish_reading)
				{
					break;
				}
				else
				{
					current_iterator++;
				}
			}
		} };

		std::string key_string{};
		std::string value_string{};

		auto ch_iterator{ line_to_parse.begin() };
		auto end_iterator{ line_to_parse.end() };

		while (ch_iterator != end_iterator)
		{
			switch (*ch_iterator)
			{
			case BEGIN_KEY:
			{
				read_key_or_value(key_string, ++ch_iterator, end_iterator);
			}
			break;
			case BEGIN_VALUE:
			{
				read_key_or_value(value_string, ++ch_iterator, end_iterator);
			}
			break;
			default:
			{
				ch_iterator++;
			}
			break;
			}
		}

		//1. Iterate string of characters until the end
		//2. If '*' concat key_string until you'll find '*' or ':', ignore '\t' and '\v'
		//3. If ':' concat value_string until you'll find '*' or ':', ignore '\t' and '\v'
		//4. Advance to the next character

		//The following line:
		//*first*part: : STRI:NG_TEST*:
		//*(first)*(part):( ):( STRI):(NG_TEST)*():()
		//Will be read as: key*(firstpart) value:(  STRING_TEST)

		if (!key_string.empty() && !value_string.empty())
		{
			text_cache_.emplace(key_string, value_string);
		}
	}

	bool PisteLanguage::ReadFile(StringViewT file_path)
	{
		if (std::ifstream lang_file(file_path.data(), std::ios::in); lang_file)
		{
			text_cache_.clear();
			for (StringT line{}; std::getline(lang_file, line);)
			{
				ParseLine(line);
			}
			return true;
		}
		return false;
	}

	bool PisteLanguage::KeyExists(const StringViewT key_name) const
	{
		return (text_cache_.count(key_name.data()) > size_t{ 0 });
	}

	PisteLanguage::StringViewT PisteLanguage::GetText(const StringViewT key_name) const
	{
		return StringViewT{ text_cache_.at(key_name.data()) };
	}

	PisteLanguage::StringT PisteLanguage::CopyText(const StringViewT key_name) const
	{
		return StringT{ text_cache_.at(key_name.data()) };;
	}

	void PisteLanguage::ChangeText(const StringViewT key_name, const StringViewT new_text)
	{
		text_cache_[key_name.data()] = StringT{ new_text.data() };
	}
}