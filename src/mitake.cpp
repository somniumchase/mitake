/*
	Copyright 2023 Somnium Chase

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

#include "mitake.h"
#include "picosha2.h"

std::vector<uint8_t> MITAKE::getHash(const std::vector<uint8_t>& data)
{
	std::vector<uint8_t> hash(picosha2::k_digest_size);
	picosha2::hash256(data, hash);
	return hash;
}

void MITAKE::writePoint(std::vector<uint8_t>& data, const Point& point)
{
	data.emplace_back(point.tag);
	data.emplace_back(point.x);
	data.emplace_back(point.y);
}

void MITAKE::writePoints(std::vector<uint8_t>& data, const std::vector<Point>& points)
{
	for (uint32_t i = 0; i < points.size(); ++i) {
		data.emplace_back(points[i].tag);
		data.emplace_back(points[i].x);
		data.emplace_back(points[i].y);
	}
}

void MITAKE::initHeader(Header& header, const std::vector<Point>& points, const std::vector<uint8_t>& hash)
{
	header.magic  = MAGIC;
	header.size   = points.size() * sizeof(Point) + sizeof(Header);
	header.tags   = points.size();
	header.verson = VERSION;

	for (uint32_t i = 0; i < 32; ++i) {
		header.hash[i] = hash[i];
	}
}
