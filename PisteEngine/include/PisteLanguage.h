#pragma once

#include<string>
#include<string_view>
#include<cstdint>
#include<map>

namespace pe
{
	//Language file format
	//'*'(asterisk) begin key
	//':'(colon) begin value, ignores '\t' signs after ':'
	//Sample:
	/*
		TEST (random string)
		------------------------------------- (random string)
		*string_key:\t\t\t(horizontal tabs)string value 123\n (key-value pair)
		*second_string_key:\t\t\tstring value test\n (key-value pair)
	*/

	class PisteLanguage
	{
	public:

		//TODO: wstring (+ localization?)
		using StringViewT = std::string_view;
		using StringT = std::string;

	private:

		///Key - string key, Value - string value
		std::map<StringT, StringT> text_cache_;

		///Parse file line
		void ParseLine(const std::string_view line_to_parse);

	public:

		///Constructs empty 
		PisteLanguage();

		///Construct + ReadFile
		PisteLanguage(const StringViewT file_path);

		///Parse text file, populate cache
		///Throws if path is not vald or file doesn't exist
		bool ReadFile(const StringViewT file_path); //Lue_Tieosto

		///Clear stored cache
		void EmptyCache() noexcept { text_cache_.clear(); };

		///Check if given key exists.
		bool KeyExists(const StringViewT key_name) const; //Hae_Indeksi

		///Get string_view to stored text, ReadFile and EmptyCache invalidate returned object.
		///Throws if key_name is not valid key
		StringViewT GetText(const StringViewT key_name) const; //Hae_Teksti

		///Get copy of the stored text.
		///Throws if key_name is not valid key
		StringT CopyText(const StringViewT key_name) const;

		///Edit stored text under specific key.
		void ChangeText(const StringViewT key_name, const StringViewT new_text); //Korvaa_Teksti
	};
}