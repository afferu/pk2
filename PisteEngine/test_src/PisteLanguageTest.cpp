#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include <PisteLanguage.h>

static std::string test_file_path{};

int main(int argc, char** argv)
{
	if (argc > 1) {
		test_file_path = std::string{ argv[1] };
	}
	else
	{
		return 1;
	}

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(PisteLanguageTests, CreationTest)
{
	pe::PisteLanguage language{};
}

TEST(PisteLanguageTests, CreationNoFileTest)
{
	EXPECT_THROW({
		pe::PisteLanguage language{ "" }; //invalid file path
		}, std::runtime_error);
}

TEST(PisteLanguageTests, CreationReadFileTest)
{
	ASSERT_NO_THROW({
		pe::PisteLanguage language{test_file_path}; //valid file path
		});
}

TEST(PisteLanguageTests, CreationSeparateReadFileTest)
{
	pe::PisteLanguage language{};
	ASSERT_NO_THROW({
		language.ReadFile(test_file_path); //valid file path
		});
}

TEST(PisteLanguageTests, OperationsTest)
{
	pe::PisteLanguage language{ test_file_path }; //valid file path

	constexpr auto invalid_key_name{ "213213rwfdseerfafsd" };

	ASSERT_FALSE(language.KeyExists(invalid_key_name)); //invalid key
	EXPECT_THROW({
		auto str_v{ language.GetText(invalid_key_name) };
		}, std::out_of_range);
	EXPECT_THROW({
		auto str{ language.CopyText(invalid_key_name) };
		}, std::out_of_range);

	constexpr auto valid_key_name{ "test string 4" };
	constexpr auto valid_key_value{ "String 4" };
	constexpr auto new_key_value{ "New string value" };

	ASSERT_TRUE(language.KeyExists(valid_key_name));

	ASSERT_NO_THROW({
		auto str_value_view{ language.GetText(valid_key_name) };
		ASSERT_EQ(str_value_view, valid_key_value);
		});

	ASSERT_NO_THROW({
		auto str_copy{ language.CopyText(valid_key_name) };
		ASSERT_EQ(str_copy, valid_key_value);
		});

	language.ChangeText(valid_key_name, new_key_value);
	ASSERT_NO_THROW({
		auto str_v{ language.GetText(valid_key_name) };
		auto str_copy{ language.CopyText(valid_key_name) };
		ASSERT_EQ(str_v, new_key_value);
		ASSERT_EQ(str_copy, new_key_value);
		});
}