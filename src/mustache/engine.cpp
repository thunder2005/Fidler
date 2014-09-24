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

#include "to_string.hpp"
#include "engine.hpp"
#include "context.hpp"
#include <regex>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <fidler/util/case_convert.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace mustache
{

Renderer::Renderer(Engine const& self, std::ostream& out) :
		self(self), out(out)
{
}

Engine::Iter Renderer::ignore() const
{
	std::ostream null(nullptr);
	return self.render(Context(), null);
}

Engine::Iter Renderer::render(Context const& obj) const
{
	return self.render(obj, out);
}

Engine::Engine(std::string path) :
		path(std::move(path)), tag_regex("<%(C |P |S |U |#|!|/|\\^|>)?(.+?)%>")
{
}

Template const* Engine::load_template(std::string const& name) const
{
	auto const inserted = templates.insert({name, {}});
	if (inserted.second)
	{
		inserted.first->second.load(this->path + name + ".mustache");
	}
	return &inserted.first->second;
}

Engine::Iter Engine::render(Context const& ctx, std::ostream& out) const
{
	Iter begin = ctx.begin();
	Iter end = ctx.end();

	std::match_results<Iter> matches;
	while (regex_search(begin, end, matches, tag_regex))
	{
		std::copy(begin, matches[0].first, std::ostreambuf_iterator<char>(out));
		begin = matches[0].second;

		std::string const modifier(matches[1].first, matches[1].second);

		if (modifier == "!")
		{
			continue;
		}

		std::string key(matches[2].first, matches[2].second);
		boost::trim(key);
		auto const tag = Tag{key, matches[0].first, matches[0].second};

		if (modifier == "/")
		{
			ctx.check_end(tag);
			return begin;
		}

		if (modifier == ">")
		{
			auto const tpl = this->load_template(key);
			auto const sub = Context(ctx, *tpl, tag);
			render(sub, out);
			continue;
		}

		auto const val = Context(ctx, tag);
		Context const& value = (key == "this") ? ctx : val;

		if (modifier == "#")
		{
			Renderer renderer(*this, out);
			begin = value ? value.render(renderer) : renderer.ignore();
			continue;
		}

		if (modifier == "^")
		{
			Renderer renderer(*this, out);
			begin = value ? renderer.ignore() : ctx.render(renderer);
			continue;
		}

		auto str = value.to_string();

		switch (modifier[0])
		{
		case 'C':
			fidler::camel_case(str);
			break;
		case 'P':
			fidler::pascal_case(str);
			break;
		case 'S':
			fidler::snake_case(str);
			break;
		case 'U':
			fidler::upper_case(str);
			break;
		default:
			break;
		}

		out << str;
	}

	std::copy(begin, end, std::ostreambuf_iterator<char>(out));
	return end;
}

} // namespace mustache
