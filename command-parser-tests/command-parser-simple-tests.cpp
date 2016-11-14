#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <iostream>
#include "../command-parser-simple/command-parser-simple.h"
using boost::test_tools::output_test_stream;

struct cout_redirect {
	cout_redirect(std::streambuf * new_buffer)
		: old(std::cout.rdbuf(new_buffer))
	{ }

	~cout_redirect() {
		std::cout.rdbuf(old);
	}

private:
	std::streambuf * old;
};

BOOST_AUTO_TEST_SUITE(test_simple_values)

BOOST_AUTO_TEST_CASE(test_01)
{
	output_test_stream output("..\\test-files\\test_01_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_01.txt") == EXIT_SUCCESS);
	}

	BOOST_REQUIRE(output.match_pattern());

}

BOOST_AUTO_TEST_CASE(test_02)
{
	output_test_stream output("..\\test-files\\test_02_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_02.txt") == EXIT_SUCCESS);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_03)
{
	output_test_stream output("..\\test-files\\test_03_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_03.txt") == EXIT_SUCCESS);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_04)
{
	output_test_stream output("..\\test-files\\test_04_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_04.txt") == EXIT_SUCCESS);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_05)
{
	output_test_stream output("..\\test-files\\test_05_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_05.txt") == EXIT_SUCCESS);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_06)
{
	output_test_stream output("..\\test-files\\test_06_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_06.txt") == EXIT_SUCCESS);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_07)
{
	output_test_stream output("..\\test-files\\test_07_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_07.txt") == EXIT_SUCCESS);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_08)
{
	output_test_stream output("..\\test-files\\test_08_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_08.txt") == EXIT_FAILURE);
	}

	BOOST_CHECK(output.match_pattern());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(test_simple_errors)

BOOST_AUTO_TEST_CASE(test_error_file_not_find)
{
	output_test_stream output("..\\test-files\\test_error_file_not_find_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_error_file_not_find.txt") == EXIT_FAILURE);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_error_01)
{
	output_test_stream output("..\\test-files\\test_error_01_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_error_01.txt") == EXIT_FAILURE);
	}
	
	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_error_02)
{
	output_test_stream output("..\\test-files\\test_error_02_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_error_02.txt") == EXIT_FAILURE);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_error_03)
{
	output_test_stream output("..\\test-files\\test_error_03_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_error_03.txt") == EXIT_FAILURE);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_error_04)
{
	output_test_stream output("..\\test-files\\test_error_04_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_error_04.txt") == EXIT_FAILURE);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_error_05)
{
	output_test_stream output("..\\test-files\\test_error_05_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_error_05.txt") == EXIT_FAILURE);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_error_06)
{
	output_test_stream output("..\\test-files\\test_error_06_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_error_06.txt") == EXIT_FAILURE);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_CASE(test_error_07)
{
	output_test_stream output("..\\test-files\\test_error_07_result.txt", true);
	{
		cout_redirect guard(output.rdbuf());

		BOOST_REQUIRE(process("..\\test-files\\test_error_07.txt") == EXIT_FAILURE);
	}

	BOOST_CHECK(output.match_pattern());
}

BOOST_AUTO_TEST_SUITE_END()