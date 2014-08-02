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

#ifndef FRANCA_TYPESYSTEM_GRAMMAR_HPP
#define FRANCA_TYPESYSTEM_GRAMMAR_HPP

#include "typesystem_types.hpp"
#include "comment_grammar.hpp"
#include "expression_grammar.hpp"

#include <boost/spirit/include/qi_nonterminal.hpp>
#include <boost/spirit/include/qi_symbols.hpp>

namespace franca
{

class TypeGrammar:
		public boost::spirit::qi::grammar<const char*, SkipGrammar, Type()>
{
public:
	TypeGrammar();

private:
	template<typename T>
	using Rule = boost::spirit::qi::rule<const char*, SkipGrammar, T>;

	Rule<Type()> type_;

	Rule<std::string()> type_ref_;
	Rule<IntegerInterval()> integer_interval_;

	boost::spirit::qi::symbols<char, BuiltinType> builtin_type_;

	Rule<std::string()> fqn_;
	Rule<std::string()> id_;
};

class TypeDefinitionGrammar:
		public boost::spirit::qi::grammar<const char*, SkipGrammar, TypeDefinition()>
{
public:
	TypeDefinitionGrammar();

private:
	template<typename T>
	using Rule = boost::spirit::qi::rule<const char*, SkipGrammar, T>;

	Rule<TypeDefinition()> type_definition_;

	TypeGrammar type_;
	ExpressionGrammar expression_;

	Rule<ArrayType()> array_type_;
	Rule<EnumerationType()> enumeration_type_;
	Rule<StructType()> struct_type_;
	Rule<UnionType()> union_type_;
	Rule<MapType()> map_type_;
	Rule<AliasType()> alias_type_;

	Rule<Enumerator()> enumerator_;
	Rule<Field()> field_;

	Rule<std::string()> fqn_;
	Rule<std::string()> id_;
};

} // namespace franca

#endif /* FRANCA_TYPESYSTEM_GRAMMAR_HPP */