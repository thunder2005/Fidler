// Copyright (c) 2014, Daniel Pfeifer <daniel@pfeifer-mail.de>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#include <fstream>
#include <boost/spirit/home/qi/parse.hpp>

#include "franca/comment_grammar.hpp"
#include "franca/model_grammar.hpp"

int main(int argc, char* argv[])
{
	std::cout << "Parsing " << argv[1] << std::endl;

	std::ifstream file(argv[1]);
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content = buffer.str();

	franca::SkipGrammar skip;
	franca::ModelGrammar grammar;

	const char* begin = content.c_str();
	const char* end = begin + content.length();

	bool ok = boost::spirit::qi::phrase_parse(begin, end, grammar, skip);
	return (ok && begin == end) ? 0 : -1;
}