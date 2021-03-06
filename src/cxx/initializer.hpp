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

#ifndef FIDLER_CXX_INITIALIZER_HPP
#define FIDLER_CXX_INITIALIZER_HPP

#include "expression.hpp"
#include "../util/karma.hpp"

#include <fidler/ast/initializer.hpp>
namespace ast = fidler::ast;

namespace cxx
{

class InitializerGrammar:
		public util::karma_grammar<ast::InitializerExpression()>
{
public:
	InitializerGrammar();

private:
	util::karma_rule<ast::InitializerExpression()> initializer_;
	util::karma_rule<ast::FieldInitializer()> field_initializer_;
	util::karma_rule<ast::ElementInitializer()> element_initializer_;
	util::karma_rule<ast::CompoundInitializer()> compound_initializer_;
	util::karma_rule<ast::BracketInitializer()> bracket_initializer_;

	ExpressionGrammar expression_;
};

} // namespace cxx

#endif /* FIDLER_CXX_INITIALIZER_HPP */
