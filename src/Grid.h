#pragma once

/*
   Copyright (C) 2018 Pharap (@Pharap)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <cstddef>
#include <limits>
#include <array>

template< typename Type, std::size_t width, std::size_t height >
class Grid;

template< typename Type >
class Grid<Type, 0, 0>
{
public:
	static constexpr std::size_t width = 0;
	static constexpr std::size_t height = 0;
	static constexpr std::size_t cellCount = 0;

private:
	using ArrayType = std::array<Type, cellCount>;

public:
	using value_type = typename ArrayType::value_type;
	using size_type = typename ArrayType::size_type;

public:
	static constexpr size_type firstX = 0;
	static constexpr size_type lastX = 0;

	static constexpr size_type firstY = 0;
	static constexpr size_type lastY = 0;

public:
	constexpr size_type getWidth() const
	{
		return width;
	}

	constexpr size_type getHeight() const
	{
		return height;
	}

	constexpr size_type getCellCount() const
	{
		return this->items.size();
	}
};

template< typename Type, std::size_t heightValue >
class Grid<Type, 0, heightValue>
{
public:
	static constexpr std::size_t width = 0;
	static constexpr std::size_t height = heightValue;
	static constexpr std::size_t cellCount = height;

private:
	using ArrayType = std::array<Type, cellCount>;

public:
	using value_type = typename ArrayType::value_type;
	using size_type = typename ArrayType::size_type;

public:
	static constexpr size_type firstX = 0;
	static constexpr size_type lastX = 0;

	static constexpr size_type firstY = 0;
	static constexpr size_type lastY = (height - 1);

public:
	constexpr size_type getWidth() const
	{
		return width;
	}

	constexpr size_type getHeight() const
	{
		return height;
	}

	constexpr size_type getCellCount() const
	{
		return this->items.size();
	}

	void fill(const value_type & value)
	{
		this->items.fill(value);
	}

	value_type & getCell(size_type x, size_type y)
	{
		static_cast<void>(x);
		return this->items[y];
	}

	constexpr const value_type & getCell(size_type x, size_type y) const
	{
		static_cast<void>(x);
		return this->items[y];
	}
};

template< typename Type, std::size_t widthValue >
class Grid<Type, widthValue, 0>
{
public:
	static constexpr std::size_t width = widthValue;
	static constexpr std::size_t height = 0;
	static constexpr std::size_t cellCount = width;

private:
	using ArrayType = std::array<Type, cellCount>;

public:
	using value_type = typename ArrayType::value_type;
	using size_type = typename ArrayType::size_type;

public:
	static constexpr size_type firstX = 0;
	static constexpr size_type lastX = (width - 1);

	static constexpr size_type firstY = 0;
	static constexpr size_type lastY = 0;

public:
	constexpr size_type getWidth() const
	{
		return width;
	}

	constexpr size_type getHeight() const
	{
		return height;
	}

	constexpr size_type getCellCount() const
	{
		return this->items.size();
	}

	void fill(const value_type & value)
	{
		this->items.fill(value);
	}

	value_type & getCell(size_type x, size_type y)
	{
		static_cast<void>(y);
		return this->items[x];
	}

	constexpr const value_type & getCell(size_type x, size_type y) const
	{
		static_cast<void>(y);
		return this->items[x];
	}
};

template< typename Type, std::size_t widthValue, std::size_t heightValue >
class Grid
{
public:
	static constexpr std::size_t width = widthValue;
	static constexpr std::size_t height = heightValue;
	static constexpr std::size_t cellCount = (width * height);
	
	static_assert(((std::numeric_limits<std::size_t>::max() / width) > height), "width * height overflows std::size_t");
	static_assert(((std::numeric_limits<std::size_t>::max() / height) > width), "width * height overflows std::size_t");

private:
	using ArrayType = std::array<Type, cellCount>;

public:
	using value_type = typename ArrayType::value_type;
	using size_type = typename ArrayType::size_type;

public:
	static constexpr size_type firstX = 0;
	static constexpr size_type lastX = (width - 1);

	static constexpr size_type firstY = 0;
	static constexpr size_type lastY = (height - 1);

private:
	ArrayType items;

	inline size_type flattenIndex(size_type x, size_type y) const
	{
		return ((width * y) + x);
	}

public:
	constexpr size_type getWidth() const
	{
		return width;
	}

	constexpr size_type getHeight() const
	{
		return height;
	}

	constexpr size_type getCellCount() const
	{
		return this->items.size();
	}

	void fill(const value_type & value)
	{
		this->items.fill(value);
	}

	value_type & get(size_type x, size_type y)
	{
		return this->items[flattenIndex(x, y)];
	}

	constexpr const value_type & get(size_type x, size_type y) const
	{
		return this->items[flattenIndex(x, y)];
	}
};